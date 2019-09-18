#include "nxServer.h"
#include "htmlData.h"
#include <EEPROM.h>

nxServer::nxServer(uint8_t portNum) : _server(portNum)
{
}

bool nxServer::begin()
{
    WiFi.mode(WIFI_AP_STA);
    bool connected = WiFi.begin(serverSSID, serverPassword);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    connected = WiFi.status() == WL_CONNECTED;
    if (connected)
    {
        _setupServerRoutes();
        auto it = _customControllers.begin();
        while (it != _customControllers.end())
        {
            _server.on(it->route, it->method, it->fn);
            it++;
        }
        _server.begin();
    }

    return _connectionEstablished = connected;
}

void nxServer::_setupServerRoutes()
{
    _server.on(F("/"), HTTP_GET, std::bind(&nxServer::_VC_IndexPage, this));
    _server.on(F("/status"), HTTP_GET, std::bind(&nxServer::_VC_StatusPage, this));
    _server.on(F("/config"), HTTP_GET, std::bind(&nxServer::_VC_ConfigPage, this));
    _server.onNotFound(std::bind(&nxServer::_VC_NotFoundPage, this));

    _server.on(F("/api/bootstrap.css"), HTTP_GET, std::bind(&nxServer::_GET_Bootstrap, this));
    _server.on(F("/api/led"), HTTP_POST, std::bind(&nxServer::_POST_LED, this));
    _server.on(F("/api/getStatus"), HTTP_GET, std::bind(&nxServer::_GET_status, this));
    _server.on(F("/api/configureServer"), HTTP_POST, std::bind(&nxServer::_POST_ConfigureServer, this));
}

void nxServer::addCustomController(nxServer::FunctionData fnData)
{
    auto finalFunc = [fnData, this]() {
        fnData.fn();                                                                                      //execute the custom function
        this->_server.send(fnData.responseCode, _getContentType(fnData.contentType), fnData.ResponseMsg); //send a response
    };

    fnData.fn = finalFunc;
    _customControllers.push_back(fnData);
}

void nxServer::serverLoop()
{
    _server.handleClient();
}

bool nxServer::isConnected()
{
    return _connectionEstablished;
}

IPAddress nxServer::getIP()
{
    return WiFi.localIP();
}

void nxServer::_VC_IndexPage()
{
    _server.send(200, _getContentType(ContentType::HTML), FPSTR(indexPage));
}

void nxServer::_VC_NotFoundPage()
{
    _server.send(404, _getContentType(ContentType::TEXT), "404: Not found");
}

void nxServer::_VC_StatusPage()
{
    _server.send(200, _getContentType(ContentType::HTML), FPSTR(statusPage));
}

void nxServer::_VC_ConfigPage()
{
    _server.send(200, _getContentType(ContentType::HTML), FPSTR(configPage));
}

void nxServer::_GET_Bootstrap()
{
    _server.send(200, _getContentType(ContentType::CSS), styles);
}

void nxServer::_GET_status()
{
    const String output("{\"ssid\":\"" + WiFi.SSID() + "\", \"ip\":\"" + getIP().toString() + "\", \"apIp\":\"" + WiFi.softAPIP().toString() + "\"" + "}");
    _server.send(200, _getContentType(ContentType::TEXT), output);
}

void nxServer::_POST_ConfigureServer()
{
    /* the args order is the following
    * bool apConfig = config the microcontroller as an Access Point Server
    * string ssid;
    * string pass;
    */
    Serial.println(_server.args());
    if (!_server.args())
    {
        _server.send(400, _getContentType(ContentType::TEXT), "no Args");
        return;
    }


    //manually search for the args to avoid problems if the args order have changed
    const bool apConfig = _server.hasArg(F("apConfig"));
    String ssid;
    String pass;
    for (size_t i = 0; i < _server.args() - 1; i++)
    {
        if (_server.argName(i) == F("ssid"))
        {
            ssid = _server.arg(i);
            continue;
        }

        if (_server.argName(i) == F("pass"))
        {
            pass = _server.arg(i);
            continue;
        }
    }

    _server.send(204, _getContentType(ContentType::TEXT), F("Configured"));
}

void nxServer::_POST_LED()
{
    static bool state = false;
    state = !state;
    digitalWrite(LED_BUILTIN, state ? HIGH : LOW);
    for (size_t i = 0; i < _server.args(); i++)
    {
        //we already know an argument of type int called "Clicks" is incoming
        Serial.println(_server.arg(i));
    }

    _server.send(204, _getContentType(ContentType::TEXT));
}

const char *nxServer::_getContentType(nxServer::ContentType contentType)
{
    switch (contentType)
    {
    case ContentType::TEXT:
        return "text/plain";
    case ContentType::HTML:
        return "text/html";
    case ContentType::CSS:
        return "text/css";
    default:
        return "text/plain";
    }
}