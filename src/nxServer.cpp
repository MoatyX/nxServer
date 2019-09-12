#include "nxServer.h"
#include "index.h"
#include "statusPage.h"
#include "configPage.h"

nxServer::nxServer(uint8_t portNum) : _server(portNum) {
}

bool nxServer::begin() {
    WiFi.mode(WIFI_AP_STA);
    bool connected = WiFi.begin(serverSSID, serverPassword);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    connected = true;
    }
    if(connected) {
        _server.on("/", std::bind(&nxServer::_handleIndexPage, this));
        _server.onNotFound(std::bind(&nxServer::_handleNotFoundPage, this));
        _server.on("/status", std::bind(&nxServer::_handleStatusPage, this));
        _server.on("/config", std::bind(&nxServer::_handleConfigPage, this));
        auto it = _customControllers.begin();
        while(it != _customControllers.end())
        {
            _server.on(it->route, it->method, it->fn);
            it++;
        }
        _server.begin();
    }
    
    _connectionEstablished = connected;
}

void nxServer::addCustomController(nxServer::FunctionData fnData) {
    auto finalFunc = [fnData, this]() {
        fnData.fn();    //execute the custom function
        this->_server.send(fnData.responseCode, _getContentType(fnData.contentType), fnData.ResponseMsg);       //send a response
    };

    fnData.fn = finalFunc;
    _customControllers.push_back(fnData);
}

void nxServer::serverLoop() {
    _server.handleClient();
}

bool nxServer::isConnected() {
    return _connectionEstablished;
}

IPAddress nxServer::getIP() {
    return WiFi.localIP();
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

char* nxServer::_getContentType(nxServer::ContentType contentType) {
    switch (contentType)
    {
    case ContentType::TEXT:
    return "text/html";
    case ContentType::JSON:
    return "json";
    default:
        return "text/html";
    }
}