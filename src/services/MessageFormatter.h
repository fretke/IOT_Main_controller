#ifndef MESSAGE_FORMATTER
#define MESSAGE_FORMATTER

#include <ArduinoJson.h>

class MessageFormatter
{
public:
    MessageFormatter() = delete;
    static void Format(char *emptyContainer, const char *entity, int &value)
    {
        DynamicJsonDocument doc(1024);
        doc["entity"] = entity;
        doc["value"] = value;

        char dst[100];

        serializeJson(doc, dst);

        sprintf(emptyContainer, "%s\r", dst);
    }
};

#endif