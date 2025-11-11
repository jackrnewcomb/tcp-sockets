/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 11/10/2025
Description:
main execution for the server.exe, handles user input sanitization, constructs the Server, and enables listening
*/

#include "Server.hpp"
#include <iostream>
#include <string>

/**
 * @brief A user-input sanitization function
 *
 * @param A vector of user-inputted arg strings
 */
bool sanitizeInput(const std::string &userInput)
{
    // Define an invalid input str, if its needed later
    std::string invalidMsg = "Invalid command line argument detected : " + userInput +
                             "\nPlease check your values and press any key to end the program!";

    // Try casting the port input to an int. If it fails, the user inputted an invalid string
    int port;
    try
    {
        port = std::stoi(userInput);
    }
    catch (...)
    {
        // Print the invalid message str
        std::cout << invalidMsg;
        return false;
    }

    // If port is not within the valid port range. Also implicitly handles error catching for negative ports
    if (port < 61000 || port > 65535)
    {
        // Print the invalid message str
        std::cout << invalidMsg;
        return false;
    }
    return true;
}

/**
 * @brief main execution, handles initial input, construction of the Server, and enables listening
 *
 * @param user-inputted console args
 */
int main(int argc, char *argv[])
{
    // Check that the right number of args were passed
    if (argc != 2)
    {
        std::cout << "Invalid number of args passed: Expected 1. Aborting\n";
        return -1;
    }

    std::string userPort = argv[1];

    // Sanitize input
    bool clean = sanitizeInput(userPort);
    if (!clean)
    {
        return -1;
    }

    // Construct the server and enable listening
    int port = std::stoi(userPort);
    Server server(port);
    server.listen();

    return 0;
}
