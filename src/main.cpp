#include <Arduino.h>

#include "basicIO.h"
#include "OperationModes.h"
#include "nxServer.h"

OperationModes mode;
nxServer server(80);


void setup() {
  Serial.begin(9600);
  Serial.flush();
  WiFi.disconnect();
  Serial.println("\n\n\n");
  Serial.println("**System Ready**");
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 

  bool modeInited = false;
  do{
    Serial.println("Initiating the Server mode....");
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