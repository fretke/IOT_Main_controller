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
        int i = 0;
        // read all
        while (comm.available() > 0 || i > MAX_BUFF_SIZE)
        {
            _buffer[i] = comm.read();
            if (_buffer[i] == 13)
            {
                Serial.println("last");
            }

            i++;
        }

        dispatchEvent(_buffer);

        send("ACK");

        clearBuff();
    }
}

void Bridge::clearBuff()
{
    for (int i = 0; i < MAX_BUFF_SIZE; i++)
    {
        _buffer[i] = 0;
    }
}

void Bridge::send(char *data)
{
    comm.write(data);
}

char *Bridge::getFormatedMessage(char *data)
{
    int size = sizeof(data);
    char buff[size + 1];

    buff[size + 1] = 13;

    for (int i = 0; i < size; i++)
    {
        buff[i] = data[i];
    }
    return buff;
}
