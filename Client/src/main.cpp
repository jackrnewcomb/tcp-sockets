/*
Author: Jack Newcomb
Class: ECE6122
Last Date Modified: 11/10/2025
Description:
main execution for the client.exe, handles user input sanitization, constructs the Client, and enables message prompts
*/

#include "Client.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief A user-input sanitization function
 *
 * @param A vector of user-inputted arg strings
 */
bool sanitizeInput(const std::vector<std::string> &userInput)
{
    // Define an invalid input str, if its needed later
    std::string invalidMsg = "Invalid command line argument detected : " + userInput[1] +
                             "\nPlease check your values and press any key to end the program!";

    // Try casting the port input to an int. If it fails, the user inputted an invalid string
    int port;
    try
    {
        port = std::stoi(userInput[1]);
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
 * @brief main execution, handles initial input, construction of the Client, and the message prompting loop
 *
 * @param user-inputted console args
 */
int main(int argc, char *argv[])
{
    // Check that the right number of args were passed
    if (argc != 3)
    {
        std::cout << "Invalid number of args passed: Expected 2. Aborting\n";
        return -1;
    }

    std::string ipAddress = argv[1];
    std::string userPort = argv[2];

    // Sanitize input
    bool clean = sanitizeInput({ipAddress, userPort});
    if (!clean)
    {
        return -1;
    }

    // Construct the client
    int port = std::stoi(userPort);
    std::shared_ptr<Client> client;
    try
    {
        client = std::make_shared<Client>(port, ipAddress);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what();
        return -1;
    }

    // Loop to prompt user input
    bool continuePrompting = true;
    while (continuePrompting)
    {
        continuePrompting = client->promptMessage();
    }
    std::cout << "Disconnection requested, terminating.\n";
    return 0;
}
