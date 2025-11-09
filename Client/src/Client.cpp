
#include "Client.hpp"

Client::Client(const int port)
{
    port_ = port;
    // Create a TCP socket
    sf::TcpSocket socket;

    // Connect to server
    sf::IpAddress serverAddress(127, 0, 0, 1); // Localhost

    std::cout << "TCP Client starting..." << std::endl;
    std::cout << "Connecting to: " << serverAddress << ":" << port_ << std::endl;

    sf::Socket::Status status = socket.connect(serverAddress, port_, sf::seconds(5));

    if (status != sf::Socket::Status::Done)
    {
        std::cerr << "Error: Could not connect to server" << std::endl;
        if (status == sf::Socket::Status::Error)
        {
            std::cerr << "Socket error occurred" << std::endl;
        }
        else if (status == sf::Socket::Status::Disconnected)
        {
            std::cerr << "Connection was disconnected" << std::endl;
        }
        // abort
    }

    std::cout << "Connected to server!" << std::endl;
    std::cout << "Local endpoint: " << socket.getLocalPort() << std::endl;
    std::cout << "Starting communication...\n" << std::endl;

    // Set non-blocking mode for receiving
    socket.setBlocking(false);

    uint32_t sequenceNum = 0;
    uint32_t packetsSent = 0;
    uint32_t packetsReceived = 0;
}

void Client::promptMessage()
{
    std::string fullSentence;
    std::cout << "Please enter a message: ";
    std::getline(std::cin, fullSentence);
}
