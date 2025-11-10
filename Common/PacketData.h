#ifndef PACKET_DATA_H
#define PACKET_DATA_H

#include <cstdint>
#include <cstdio>
#include <cstring>

// Custom structure for transferring data over UDP
struct PacketData
{
    char message[64]; // Text message

    // Constructor
    PacketData()
    {
        memset(message, 0, sizeof(message));
    }

    // Helper method to set message
    void setMessage(const char *msg)
    {
        strncpy(message, msg, sizeof(message) - 1);
        message[sizeof(message) - 1] = '\0';
    }

    // Helper method to print data
    void print() const
    {
        printf("Message: %s\n", message);
    }

    // Helper method to return string data
    char *toString()
    {
        return message;
    }
};

#endif // PACKET_DATA_H
