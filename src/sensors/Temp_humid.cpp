#include "./Temp_Humid.h"
#include "../services/MessageFormatter.h"

TempHumidSensor::TempHumidSensor(Bridge *bridge, const int &pin, const int &interval)
    : _bridge(bridge), _pin(pin), _interval(interval)
{
    _sensor = new DHT_Unified(_pin, DHT_TYPE);
}

TempHumidSensor::~TempHumidSensor()
{
    delete _sensor;
}

void TempHumidSensor::init()
{
    _sensor->begin();
    getDetails();
}

void TempHumidSensor::loop()
{
    static unsigned long lastEventTime = millis();
    if ((millis() - lastEventTime) > _interval)
    {
        sensors_event_t event;
        _sensor->temperature().getEvent(&event);

        if (!isnan(event.temperature))
        {
            Serial.println("temperature");
            Serial.println(event.temperature);
            char message[100];

            MessageFormatter::Format(message, "temperature", event.temperature);
            Serial.println(message);
            _bridge->send(message);
        }
        lastEventTime = millis();
    }
}

void TempHumidSensor::getDetails()
{
    sensor_t sensor;
    _sensor->temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print(F("Sensor Type: "));
    Serial.println(sensor.name);
    Serial.print(F("Driver Ver:  "));
    Serial.println(sensor.version);
    Serial.print(F("Unique ID:   "));
    Serial.println(sensor.sensor_id);
    Serial.print(F("Max Value:   "));
    Serial.print(sensor.max_value);
    Serial.println(F("°C"));
    Serial.print(F("Min Value:   "));
    Serial.print(sensor.min_value);
    Serial.println(F("°C"));
    Serial.print(F("Resolution:  "));
    Serial.print(sensor.resolution);
    Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));

    _sensor->humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print(F("Sensor Type: "));
    Serial.println(sensor.name);
    Serial.print(F("Driver Ver:  "));
    Serial.println(sensor.version);
    Serial.print(F("Unique ID:   "));
    Serial.println(sensor.sensor_id);
    Serial.print(F("Max Value:   "));
    Serial.print(sensor.max_value);
    Serial.println(F("%"));
    Serial.print(F("Min Value:   "));
    Serial.print(sensor.min_value);
    Serial.println(F("%"));
    Serial.print(F("Resolution:  "));
    Serial.print(sensor.resolution);
    Serial.println(F("%"));
}