#include "Client.hpp"
#include <iostream>
#include <string>
#include <vector>

bool sanitizeInput(const std::vector<std::string> &userInput)
{
    std::string invalidMsg = "Invalid command line argument detected : " + userInput[1] +
                             "\nPlease check your values and press any key to end the program!";
    int port;
    try
    {
        port = std::stoi(userInput[1]);
    }
    catch (...)
    {
        std::cout << invalidMsg;
        return false;
    }

    if (port < 61000 || port > 65535)
    {
        std::cout << invalidMsg;
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid number of args passed: Expected 2. Aborting\n";
        return -1;
    }

    std::string ipAddress = argv[1];
    std::string port = argv[2];

    bool clean = sanitizeInput({ipAddress, port});
    if (!clean)
    {
        return -1;
    }

    Client client;

    std::string msg;
    while (true)
    {

        client.update();
    }
    return 0;
}
