#include "nxServer.h"
#include "index.h"
#include "statusPage.h"
#include "configPage.h"

nxServer::nxServer(uint8_t portNum) : _server(portNum) {
}

bool nxServer::begin() {
    WiFi.mode(WIFI_AP);
    bool connected = WiFi.softAP(serverSSID, serverPassword);
    if(connected) {
        _server.on("/", std::bind(&nxServer::_handleIndexPage, this));
        _server.onNotFound(std::bind(&nxServer::_handleNotFoundPage, this));
        _server.on("/status", std::bind(&nxServer::_handleStatusPage, this));
        _server.on("/config", std::bind(&nxServer::_handleConfigPage, this));
        auto it = _customControllers.begin();
        while(it != _customControllers.end())
        {
            _server.on(it->first, it->second);
            it++;
        }
        _server.begin();
    }
    
    _connectionEstablished = connected;
}

void nxServer::addCustomController(nxServer::FunctionData fn) {
    auto finalFunc = [fn, this]() {
        fn.fn();    //execute the custom function
        this->_server.send(fn.responseCode, "text/html", fn.ResponseMsg);       //send a response
    };
    _customControllers.insert(std::make_pair(fn.route, finalFunc));
}

void nxServer::serverLoop() {
    _server.handleClient();
}

bool nxServer::isConnected() {
    return _connectionEstablished;
}

IPAddress nxServer::getIP() {
    return WiFi.softAPIP();
}


void nxServer::_handleIndexPage() {
    _server.send(200, "text/html", indexPage);
}

void nxServer::_handleNotFoundPage() {
    _server.send(404, "text/plain", "404: Not found");
}

void nxServer::_handleStatusPage() {
    _server.send(200, "text/html", statusPage);
}

void nxServer::_handleConfigPage() {
    _server.send(200, "text/html", configPage);
}