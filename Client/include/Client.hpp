/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 11/10/2025
Description:
Header for a Client class, with methods for prompting user input messages, and sending those messages
*/

#include "SFML/Network.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <string>

class Client
{
  public:
    /**
     * @brief Constructor for the client
     *
     * @param The port int
     * @param The address string
     */
    Client(const int port, const std::string &address);

    /**
     * @brief Prompts the user for a string input message to the console
     * @return A true or false on whether to continue prompting (based on whether the user opted to disconnect)
     */
    bool promptMessage();

    /**
     * @brief Sends the user-inputted message to the server
     *
     * @param The message to send to the server, obtained through the console via promptMessage
     */
    void sendMessage(const std::string &msg);

  private:
    int port_;                                                                  // The port number
    std::unique_ptr<sf::TcpSocket> socket_ = std::make_unique<sf::TcpSocket>(); // A pointer to the socket
};
