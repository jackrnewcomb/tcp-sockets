/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 11/10/2025
Description:
Implementation for a Server class, with methods for listening on a port, and writing to a log
*/

#include "Server.hpp"

Server::Server(const int port)
{
    // Initialize the port_ and listener_ members
    port_ = port;
    listener_ = std::make_shared<sf::TcpListener>();

    // Initialize the log (or reset, if it exists already)
    std::ofstream outputFile("server.log");
    outputFile.close();
}

void Server::listen()
{

    std::cout << "Listening on port: " << port_ << std::endl;
    std::cout << "To terminate server, input ctrl+C\n";

    if (listener_->listen(port_) != sf::Socket::Done)
    {
        std::cerr << "Failed to bind to port " << port_ << "\n";
        return;
    }

    // Create a selector
    sf::SocketSelector selector;

    // Add the listener to the selector
    selector.add(*listener_);

    // Endless loop for new connections/rx'd messages
    while (true)
    {
        // Make the selector wait for data on any socket
        if (selector.wait())
        {
            // Test the listener
            if (selector.isReady(*listener_))
            {
                // The listener is ready: there is a pending connection
                auto client = std::make_unique<sf::TcpSocket>();
                if (listener_->accept(*client) == sf::Socket::Status::Done)
                {
                    std::string msg = "Client connected from " + client->getRemoteAddress().toString() + ":" +
                                      std::to_string(client->getRemotePort()) + "\n";
                    writeToLog(msg);

                    selector.add(*client);
                    clients.push_back(std::move(client));
                }
            }
            else
            {
                // There is no pending connection. Lets check each current client for messages
                for (auto it = clients.begin(); it != clients.end();)
                {
                    // The client at iterator it
                    sf::TcpSocket &client = **it;

                    // Check if we've received a message
                    if (selector.isReady(client))
                    {
                        // We've received a message. Should be in sf::Packet form, so just call receive()
                        sf::Packet receivedData;
                        sf::Socket::Status status = client.receive(receivedData);

                        if (status == sf::Socket::Done)
                        {
                            // Copy the receivedData message to a string, and print that string to the log
                            std::string newMsg;
                            receivedData >> newMsg;

                            std::string nextWord;
                            while (receivedData >> nextWord)
                            {
                                newMsg += " " + nextWord;
                            }

                            writeToLog("New message received from from " + client.getRemoteAddress().toString() + ":" +
                                       std::to_string(client.getRemotePort()) + ": " + newMsg);

                            // Move to the next iterator
                            ++it;
                        }
                        else if (status == sf::Socket::Disconnected)
                        {
                            // We've disconnected. Print a disconnect message to the log
                            std::string msg = "Client disconnected from " + client.getRemoteAddress().toString() + ":" +
                                              std::to_string(client.getRemotePort()) + "\n";
                            writeToLog(msg);

                            // Remove the client from the selector, and from the vector of clients
                            selector.remove(client);
                            it = clients.erase(it);
                        }
                        else
                        {
                            ++it; // Not ready, move on to the next iterator
                        }
                    }
                    else
                    {
                        ++it; // Not ready, move on to the next iterator
                    }
                }
            }
        }
    }
}

void Server::writeToLog(const std::string &msg)
{
    // Open log in append mode
    std::ofstream outputFile("server.log", std::ios::app);

    // Error handling
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
    }

    // Write to file
    outputFile << msg << "\n";

    // Close file
    outputFile.close();
}
