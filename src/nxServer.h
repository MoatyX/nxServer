#ifndef NX_SERVER_H
#define NX_SERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <map>

class nxServer
{

public:
    nxServer(uint8_t portNum);

    void serverLoop();
    bool begin();

    inline bool isConnected()
    {
        return _connectionEstablished;
    }
    inline IPAddress getIP()
    {
        return WiFi.localIP();
    }
    inline IPAddress getSoftAPIP() {
        return WiFi.softAPIP();
    }

    enum ContentType
    {
        HTML,
        TEXT,
        JSON,
        CSS
    };

    typedef struct
    {
        const char *route;
        ESP8266WebServer::THandlerFunction fn;
        uint16_t responseCode;
        const char *ResponseMsg;
        ContentType contentType;
        HTTPMethod method;

    } FunctionData;

    void addCustomController(nxServer::FunctionData fn);

    bool connectTo(const String& ssid, const String& pass);

    inline const size_t getArgCount()
    {
        return _server.args();
    }

    inline const String &getArg(const int i)
    {
        return _server.arg(i);
    }

    // const char *serverSSID = "nxo";
    // const char *serverPassword = "3835783642339624";

    const char* AP_SSID = "nxServer";
    const char* AP_PASS = "bigdaddy";

private:
    bool _connectionEstablished = false;
    ESP8266WebServer _server;

    std::vector<FunctionData> _customControllers;

    //internal functions
    void _setupServerRoutes();

    //main View Controllers
    void _VC_IndexPage();
    void _VC_NotFoundPage();
    void _VC_StatusPage();
    void _VC_ConfigPage();

    //controllers
    void _GET_Bootstrap();
    void _GET_status();
    void _GET_WLANList();
    void _POST_LED();
    void _POST_ConfigureServer();

    const static char *_getContentType(const nxServer::ContentType contentType);
};

#endif