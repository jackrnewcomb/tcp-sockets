/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 11/10/2025
Description:
Header for a Server class, with methods for listening on a port, and writing to a log
*/

#include "SFML/Network.hpp"
#include <fstream>
#include <iostream>
#include <memory>

class Server
{
  public:
    /**
     * @brief Constructor for the server
     *
     * @param The port int
     */
    Server(const int port);

    /**
     * @brief Listens on the port, both for connect/disconnects, and packets sent by clients
     */
    void listen();

    /**
     * @brief Calculates the sum of two integers.
     *
     * @param The std::string message to print to logs. Typically either a connect/disconnect update, or a message
     passed by the client
     *
     */
    void writeToLog(const std::string &msg);

  private:
    int port_;                                           // The port number
    std::shared_ptr<sf::TcpListener> listener_;          // A pointer to the TcpListener
    std::vector<std::unique_ptr<sf::TcpSocket>> clients; // A vector of pointers to all active sockets
};
