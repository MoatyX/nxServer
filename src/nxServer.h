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

    enum ContentType {
        TEXT,
        JSON
    };

    typedef struct {
        const char* route;
        ESP8266WebServer::THandlerFunction fn;
        uint16_t responseCode;
        const char* ResponseMsg;
        ContentType contentType;
        HTTPMethod method;

    } FunctionData;

    void addCustomController(nxServer::FunctionData fn);

    const char* serverSSID = "nxo";
    const char* serverPassword = "3835783642339624";

private:
    bool _connectionEstablished = false;
    ESP8266WebServer _server;

    std::vector<FunctionData> _customControllers;

    //main controllers
    void _handleIndexPage();
    void _handleNotFoundPage();

    //other controllers
    void _handleStatusPage();
    void _handleConfigPage();

    char* _getContentType(nxServer::ContentType contentType);
};

#endif