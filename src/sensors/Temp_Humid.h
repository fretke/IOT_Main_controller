#ifndef TEMP_HUMID
#define TEMP_HUMID

#include <Bridge.h>

#include <DHT.h>
#include <DHT_U.h>

#define DHT_TYPE DHT11

class TempHumidSensor : public Loopable
{
private:
    DHT_Unified *_sensor;
    Bridge *_bridge;
    const int _pin;
    const int _interval;

    void getDetails();

public:
    TempHumidSensor(Bridge *bridge, const int &pin, const int &interval);

    ~TempHumidSensor();

    void loop() override;
    void init() override;
};

#endif