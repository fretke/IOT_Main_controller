#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define SLAVE_ADDR 9
#define ANSWER 5

void onReceive(int d);

SoftwareSerial slaveSerial(10, 12);

void setup()
{

  Serial.begin(9600);
  slaveSerial.begin(9600);
  Serial.println("SLAVE");
}

int incomingByte = 0;

void loop()
{
  while (slaveSerial.available() > 0)
  {
    incomingByte = slaveSerial.read();

    slaveSerial.write("pong\r");

    Serial.println(incomingByte);
  }
  delay(1000);
}
