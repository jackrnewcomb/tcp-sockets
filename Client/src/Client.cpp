
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

    sf::Packet packet;
    packet << message;

    // Send the data structure
    sf::Socket::Status sendStatus = socket_->send(packet);

    if (sendStatus != sf::Socket::Status::Done)
    {
        if (sendStatus == sf::Socket::Status::Disconnected)
        {
            std::cout << "Server disconnected" << std::endl;
        }
    }
}
