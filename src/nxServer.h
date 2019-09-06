#ifndef NX_SERVER_H
#define NX_SERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <map>

class nxServer {

public:
    nxServer(uint8_t portNum);

    void serverLoop();
    bool begin();

    bool isConnected();
    IPAddress getIP();

    typedef struct {
        const char* route;
        ESP8266WebServer::THandlerFunction fn;
        uint16_t responseCode;
        const char* ResponseMsg;
    } FunctionData;

    void addCustomController(nxServer::FunctionData fn);

    const char* serverSSID = "MoatyNXServer";
    const char* serverPassword = "bigdaddy";

private:
    bool _connectionEstablished = false;
    ESP8266WebServer _server;

    std::map<const char*, ESP8266WebServer::THandlerFunction> _customControllers;

    //main controllers
    void _handleIndexPage();
    void _handleNotFoundPage();

    //other controllers
    void _handleStatusPage();
    void _handleConfigPage();
};

#endif