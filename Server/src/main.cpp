
#include <iostream>
#include <string>

bool sanitizeInput(const std::string &userInput)
{
    std::string invalidMsg = "Invalid command line argument detected : " + userInput +
                             "\nPlease check your values and press any key to end the program!";
    int port;
    try
    {
        port = std::stoi(userInput);
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
    if (argc != 2)
    {
        std::cout << "Invalid number of args passed: Expected 1. Aborting\n";
        return -1;
    }

    std::string port = argv[2];

    bool clean = sanitizeInput(port);
    if (!clean)
    {
        return -1;
    }

    return 0;
}
