#include <Arduino.h>
#include <ArduinoJson.h>
#include <Bridge.h>

#define SENSOR_PIN A0

void checkLight();

void onBridgeData(char *data);

void sendMessage(int &value);

Bridge bridge(10, 12, 9600);

void setup()
{
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
  bridge.init();
  bridge.onEvent(onBridgeData);
  Serial.println("CONTROLLER_MODULE");
}

void loop()
{
  bridge.loop();
  checkLight();
  delay(500);
}

void sendMessage(int &value)
{
  DynamicJsonDocument doc(1024);
  doc["type"] = value;

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
}

void checkLight()
{
  static int level;
  static unsigned long lastEventTime = millis();
  if ((millis() - lastEventTime) > 500)
  {
    level = analogRead(SENSOR_PIN);
    level = map(level, 0, 1023, 0, 255);
    Serial.println("current light level");
    Serial.println(level);

    sendMessage(level);
    lastEventTime = millis();
  }
}
