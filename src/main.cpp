#include <Arduino.h>
#include "Bridge/Bridge.h"

void onBridgeData(char *data);

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
  delay(1000);
}

void onBridgeData(char *data)
{
  Serial.println(data);
}
