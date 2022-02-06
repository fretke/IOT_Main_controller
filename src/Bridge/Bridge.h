#ifndef BRIDGE
#define BRIDGE

#include "SoftwareSerial.h"
#include "services/CallBackService.h"
#include "interfaces/Loopable.h"

#define MAX_BUFF_SIZE 100

class Bridge : public CallBackService<char *>, public Loopable
{
private:
    SoftwareSerial comm;
    long _baundRate;
    char _buffer[MAX_BUFF_SIZE];
    int _currentBuffPosition = 0;

    void onMessageReceived();
    void resetBuffer();

public:
    Bridge(uint8_t rx, uint8_t tx, long baundRate);

    void loop() override;
    void init() override;
    void send(char *data);
};

#endif