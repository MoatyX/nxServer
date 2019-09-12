#include <Arduino.h>

#include "basicIO.h"
#include "OperationModes.h"
#include "nxServer.h"

BasicIO io(&Serial);
OperationModes mode;
nxServer server(80);

bool connectTo(String ssid, String pass) {
  WiFi.begin(ssid, pass);
  Serial.println("Connecting");
  while(!WiFi.isConnected())
  {
    if(WiFi.status() == WL_CONNECT_FAILED)
    {
      Serial.println();
      Serial.println("Connection failed");
      return false;
    }
    delay(100);
    Serial.print("..");
  }

  Serial.println();
  Serial.println("Connected !");
  Serial.println(WiFi.localIP());

  return true;
}

bool scanNetworks() {

  Serial.println("Scan Networks Mode");
  Serial.println("Scanning.....");

  //rest the module
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  int8_t x = WiFi.scanNetworks();
  for (int8_t i = 0; i < x; i++)
  {
    Serial.println(WiFi.SSID(i) + " = " + i);
  }

  uint8_t selectedNet = io.getNumber();
  char* pass = nullptr;

  Serial.println("Enter Password");
  io.readString(&pass);

  return connectTo(WiFi.SSID(selectedNet), pass);
}

void handleLED() {
  static bool state = false;
  state = !state;
  digitalWrite(LED_BUILTIN, state ? HIGH : LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.flush();
  WiFi.disconnect();
  Serial.println();
  Serial.println("**System Ready**");
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 

  bool modeInited = false;
  do{
    // Serial.println("Select a mode: ");
    // Serial.print("Scan For Network = ");
    // Serial.println(OperationModes::ScanConnect);
    // Serial.print("Server = ");
    // Serial.println(OperationModes::Server);
    // auto num = io.getNumber();
    // mode = static_cast<OperationModes>(num);
    // Serial.println();

    // switch (mode)
    // {
    //   case OperationModes::ScanConnect:
    //   modeInited = scanNetworks();
    //   break;
    //   case OperationModes::Server:
    //   modeInited = server.begin();
    //   break;
    // default:
    //   break;
    // }

    Serial.println("Initiating the Server mode....");
    nxServer::FunctionData data;
    data.fn = handleLED;
    data.responseCode = 204;
    data.ResponseMsg = "<h1>done</h1>";
    data.route = "/led";
    data.method = HTTP_POST;
    server.addCustomController(data);
    modeInited = server.begin();

    if(!modeInited) Serial.println("Initiation failed, trying again");

  } while (!modeInited);
  
  Serial.print("Server has started with the IP address: ");
  Serial.println(server.getIP());

  Serial.println("Init End");
}

void loop() {
  if(server.isConnected())
      server.serverLoop();
}