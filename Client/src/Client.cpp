
#include "Client.hpp"

Client::Client(const int port)
{
    port_ = port;

    // Connect to server
    sf::IpAddress serverAddress(127, 0, 0, 1); // Localhost

    std::cout << "TCP Client starting..." << std::endl;
    std::cout << "Connecting to: " << serverAddress << ":" << port_ << std::endl;

    sf::Socket::Status status = socket_->connect(serverAddress, port_, sf::seconds(5));

    if (status != sf::Socket::Status::Done)
    {
        std::cerr << "Error: Could not connect to server" << std::endl;
        if (status == sf::Socket::Status::Error)
        {
            std::cerr << "Socket error occurred" << std::endl;
        }
        else if (status == sf::Socket::Status::Disconnected)
        {
            std::cerr << "Connection was disconnected" << std::endl;
        }
        // abort
    }

    std::cout << "Connected to server!" << std::endl;
    std::cout << "Local endpoint: " << socket_->getLocalPort() << std::endl;
    std::cout << "Starting communication...\n" << std::endl;
}

void Client::promptMessage()
{
    std::string msg;
    std::cout << "Please enter a message: ";
    std::getline(std::cin, msg);
    sendMessage(msg);
}

void Client::sendMessage(const std::string &message)
{

    // Create and populate the custom data structure
    PacketData data;
    data.sequenceNumber = sequenceNum_++;

    // Simulate some moving object (circular motion)
    float t = sequenceNum_ * 0.1f;
    data.position[0] = 10.0f * std::cos(t);
    data.position[1] = 10.0f * std::sin(t);
    data.position[2] = t * 0.5f;

    data.velocity[0] = -10.0f * std::sin(t) * 0.1f;
    data.velocity[1] = 10.0f * std::cos(t) * 0.1f;
    data.velocity[2] = 0.5f;

    data.status = (sequenceNum_ % 2 == 0) ? 1 : 0;

    const char *constCharPointer = message.c_str();
    char msg[64];
    snprintf(msg, sizeof(msg), "Client packet #%u", sequenceNum_);
    data.setMessage(constCharPointer);

    // Get timestamp
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    data.timestamp = std::chrono::duration<double>(duration).count();

    // Send the data structure
    sf::Socket::Status sendStatus = socket_->send(&data, sizeof(data));

    if (sendStatus != sf::Socket::Status::Done)
    {
        if (sendStatus == sf::Socket::Status::Disconnected)
        {
            std::cout << "Server disconnected" << std::endl;
        }
        else if (sendStatus == sf::Socket::Status::Error)
        {
            std::cout << "Error sending packet " << sequenceNum_ << std::endl;
        }
    }
    else
    {
        packetsSent++;
        std::cout << "Sent packet #" << sequenceNum_ << std::endl;
    }
}
