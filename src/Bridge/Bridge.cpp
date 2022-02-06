#include "SoftwareSerial.h"
#include "services/CallBackService.h"
#include "interfaces/Loopable.h"
#include "Bridge.h"
#include "Arduino.h"

Bridge::Bridge(uint8_t rx, uint8_t tx, long baundRate)
    : comm(rx, tx), _baundRate(baundRate)
{
}

void Bridge::init()
{
    comm.begin(_baundRate);
}

void Bridge::loop()
{
    if (comm.available() > 0)
    {
        // read all
        while (comm.available() > 0)
        {
            if (_currentBuffPosition > MAX_BUFF_SIZE)
            {
                resetBuffer();
            }

            _buffer[_currentBuffPosition] = comm.read();

            if (_buffer[_currentBuffPosition] == 13)
            {

                dispatchEvent(_buffer);
                resetBuffer();
                continue;
            }

            _currentBuffPosition++;
        }
    }
}

void Bridge::onMessageReceived()
{
    dispatchEvent(_buffer);
}

void Bridge::resetBuffer()
{
    for (int i = 0; i < MAX_BUFF_SIZE; i++)
    {
        _buffer[i] = 0;
    }
    _currentBuffPosition = 0;
}

void Bridge::send(char *data)
{
    comm.write(data);
}
