#include <Arduino.h>
#include <ArduinoJson.h>
#include "Bridge/Bridge.h"

void onBridgeData(char *data);

void sendMessage();

Bridge bridge(10, 12, 9600);

void setup()
{

  Serial.begin(9600);
  bridge.init();
  bridge.onEvent(onBridgeData);
  Serial.println("SLAVE");
}

void loop()
{
  bridge.loop();
  delay(500);
}

void sendMessage()
{
  DynamicJsonDocument doc(1024);
  doc["type"] = "ack";

  char dst[100];
  char formatted[100];

  serializeJson(doc, dst);

  sprintf(formatted, "%s\r", dst);
  bridge.send(formatted);
}

void onBridgeData(char *data)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, data);

  const char *msgType = doc["type"];
  Serial.println(msgType);

  // bridge.send("ack\r");
  sendMessage();
}
