#ifndef PACKET_DATA_H
#define PACKET_DATA_H

#include <cstdint>
#include <cstdio>
#include <cstring>

// Custom structure for transferring data over UDP
struct PacketData
{
    uint32_t sequenceNumber;
    float position[3]; // x, y, z coordinates
    float velocity[3]; // vx, vy, vz
    uint8_t status;    // Status flag
    char message[64];  // Text message
    double timestamp;  // Timestamp

    // Constructor
    PacketData() : sequenceNumber(0), status(0), timestamp(0.0)
    {
        for (int i = 0; i < 3; i++)
        {
            position[i] = 0.0f;
            velocity[i] = 0.0f;
        }
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
        printf("Sequence: %u\n", sequenceNumber);
        printf("Position: [%.2f, %.2f, %.2f]\n", position[0], position[1], position[2]);
        printf("Velocity: [%.2f, %.2f, %.2f]\n", velocity[0], velocity[1], velocity[2]);
        printf("Status: %u\n", status);
        printf("Message: %s\n", message);
        printf("Timestamp: %.3f\n", timestamp);
    }
};

#endif // PACKET_DATA_H
