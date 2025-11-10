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
    std::string userPort = argv[2];

    bool clean = sanitizeInput({ipAddress, userPort});
    if (!clean)
    {
        return -1;
    }

    int port = std::stoi(userPort);
    Client client(port);

    bool running = true;
    while (running)
    {
        client.promptMessage();
        std::cout << "Input q to quit/disconnect, or any other button to continue\n";

        std::string in;
        std::getline(std::cin, in);

        if (in == "q")
        {
            running = false;
        }
    }
    return 0;
}
