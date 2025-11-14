/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 11/10/2025
Description:
Implementation for a Client class, with methods for prompting user input messages, and sending those messages
*/

#include "Client.hpp"

Client::Client(const int port, const std::string &address)
{
    // Initialize member port_
    port_ = port;

    // Connect to server
    sf::IpAddress serverAddress(address);

    sf::Socket::Status status = socket_->connect(serverAddress, port_, sf::seconds(5));

    // Add some console output handling for possible status situations
    if (status == sf::Socket::Status::Done)
    {
        std::cout << "Connected! Local port: " << socket_->getLocalPort() << "\n";
    }
    else
    {
        std::cout << "Failed to connect to the server at " + address + " on " + std::to_string(port) +
                         ". Please check your values "
                         "and press any key to end program!";
    }
}

bool Client::promptMessage()
{
    // Prompt a user inputted message
    std::string msg;
    std::cout << "Please enter a message (or input q to disconnect): ";
    std::getline(std::cin, msg);
    if (msg == "q")
    {
        return false;
    }
    else
    {
        sendMessage(msg);
        return true;
    }
}

void Client::sendMessage(const std::string &message)
{
    // Generate a packet and append the message
    sf::Packet packet;
    packet << message;

    // Send the packet
    sf::Socket::Status sendStatus = socket_->send(packet);
}
