
#include "Server.hpp"

Server::Server(const int port)
{
    port_ = port;
    listener_ = std::make_shared<sf::TcpListener>();

    // Reset log, prob move this to a function
    std::ofstream outputFile("server.log");
    outputFile.close();
}

void Server::listen()
{
    if (listener_->listen(port_) != sf::Socket::Status::Done)
    {
        std::cout << "Error: Could not bind listener to port " << port_ << std::endl;
        // abort somehow
    }

    std::cout << "TCP Server started" << std::endl;
    std::cout << "Listening on port: " << port_ << std::endl;
    std::cout << "Waiting for client connection...\n" << std::endl;

    // Create a selector
    sf::SocketSelector selector;

    // Add the listener to the selector
    selector.add(*listener_);

    // Endless loop that waits for new connections
    while (running_)
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
                else
                {
                    std::cout << "Something happened\n";
                }
            }
            else
            {
                for (auto it = clients.begin(); it != clients.end();)
                {
                    sf::TcpSocket &client = **it;

                    if (selector.isReady(client))
                    {

                        sf::Packet receivedData;
                        sf::Socket::Status status = client.receive(receivedData);

                        if (status == sf::Socket::Done)
                        {
                            std::string newMsg;
                            receivedData >> newMsg;
                            writeToLog("New message received from from " + client.getRemoteAddress().toString() + ":" +
                                       std::to_string(client.getRemotePort()) + ": " + newMsg);
                            ++it;
                        }
                        else if (status == sf::Socket::Disconnected)
                        {
                            std::string msg = "Client disconnected from " + client.getRemoteAddress().toString() + ":" +
                                              std::to_string(client.getRemotePort()) + "\n";
                            writeToLog(msg);

                            selector.remove(client);
                            it = clients.erase(it);
                        }
                        else
                        {
                            ++it; // Not ready or partial, move on
                        }
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }
    }
}

void Server::writeToLog(const std::string &msg)
{
    std::ofstream outputFile("server.log", std::ios::app);

    if (!outputFile.is_open())
    {

        std::cout << "Error opening file!" << std::endl;
    }
    outputFile << msg << "\n";

    outputFile.close();
}
