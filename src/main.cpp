#include <Arduino.h>
#include <ArduinoJson.h>
#include <Bridge.h>

#include "./services/MessageFormatter.h"
#include "./sensors/Temp_Humid.h"

#define SENSOR_PIN A0
#define DHT_PIN 52
#define RELAY_8 50

void checkLight();

void onBridgeData(char *data);

void sendMessage(int &value);

void processRelayChange(int &slot, bool &value);

Bridge bridge(10, 12, 9600);

TempHumidSensor tempSensor(&bridge, DHT_PIN, 5000);

enum ActionTypes
{
  Unknown,
  Relay
};

enum RelaySlots
{
  One = 1,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight
};

void setup()
{
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_8, OUTPUT);
  digitalWrite(RELAY_8, HIGH);
  Serial.begin(9600);
  bridge.init();
  bridge.onEvent(onBridgeData);
  Serial.println("CONTROLLER_MODULE");
  tempSensor.init();
}

void loop()
{
  bridge.loop();
  tempSensor.loop();
  checkLight();
}

void sendMessage(int &value)
{

  char message[100];

  MessageFormatter::Format(message, "lightSensor", value);

  Serial.println(message);
  bridge.send(message);
}

void onBridgeData(char *data)
{
  Serial.println("received message from wemos");
  Serial.println(data);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, data);

  int type = doc["type"];

  switch (type)
  {
  case ActionTypes::Relay:

    int slot = doc["slot"];
    bool slotState = doc["status"];
    processRelayChange(slot, slotState);
    break;

  default:
    break;
  }
}

void processRelayChange(int &slot, bool &value)
{
  int pin = -1;

  switch (slot)
  {
  case RelaySlots::Eight:
    pin = RELAY_8;
    break;

  default:
    break;
  }

  if (pin != -1)
  {
    if (value)
    {
      digitalWrite(pin, LOW);
    }
    else
    {
      digitalWrite(pin, HIGH);
    }
  }
}

void checkLight()
{
  static int level;
  static unsigned long lastEventTime = millis();
  if ((millis() - lastEventTime) > 1000)
  {
    level = analogRead(SENSOR_PIN);
    level = map(level, 0, 1023, 0, 255);
    Serial.println("current light level");
    Serial.println(level);

    sendMessage(level);
    lastEventTime = millis();
  }
}
