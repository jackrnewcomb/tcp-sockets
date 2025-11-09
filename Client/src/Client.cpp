
#include "Client.hpp"

Client::Client()
{
}

void Client::update()
{
    promptMessage();
}

void Client::promptMessage()
{
    std::string fullSentence;
    std::cout << "Please enter a message: ";
    std::getline(std::cin, fullSentence);
}
