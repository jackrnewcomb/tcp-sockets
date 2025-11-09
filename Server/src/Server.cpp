
#include "Server.hpp"

Server::Server(const int port)
{
    port_ = port;
    listener_ = std::make_shared<sf::TcpListener>();
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

    // Accept a new connection
    sf::TcpSocket client;
    if (listener_->accept(client) != sf::Socket::Status::Done)
    {
        std::cout << "Error: Could not accept client connection" << std::endl;
        // abort somehow
    }

    std::cout << "Client connected from: " << client.getRemoteAddress().toString() << ":" << client.getRemotePort()
              << std::endl;
    std::cout << "Starting bidirectional communication...\n" << std::endl;

    // Set non-blocking mode for non-blocking receives
    client.setBlocking(false);

    uint32_t sequenceNum = 0;
    uint32_t packetsReceived = 0;
    uint32_t packetsSent = 0;
}

void Server::writeLog()
{
}
/*
int main()
{

    // Accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Status::Done)
    {
        std::cerr << "Error: Could not accept client connection" << std::endl;
        return -1;
    }

    std::cout << "Client connected from: " << client.getRemoteAddress().value() << ":" << client.getRemotePort()
              << std::endl;
    std::cout << "Starting bidirectional communication...\n" << std::endl;

    // Set non-blocking mode for non-blocking receives
    client.setBlocking(false);

    uint32_t sequenceNum = 0;
    uint32_t packetsReceived = 0;
    uint32_t packetsSent = 0;

    while (true)
    {
        // Try to receive data from client
        PacketData receivedData;
        std::size_t received;
        sf::Socket::Status receiveStatus = client.receive(&receivedData, sizeof(receivedData), received);

        if (receiveStatus == sf::Socket::Status::Done)
        {
            packetsReceived++;

            std::cout << "\n=== Packet Received from Client ===" << std::endl;
            std::cout << "Size: " << received << " bytes" << std::endl;
            receivedData.print();

            // Calculate latency
            auto now = std::chrono::system_clock::now();
            auto duration = now.time_since_epoch();
            double currentTime = std::chrono::duration<double>(duration).count();
            double latency = (currentTime - receivedData.timestamp) * 1000.0;

            std::cout << "Latency: " << latency << " ms" << std::endl;
            std::cout << "Total packets received: " << packetsReceived << std::endl;
        }
        else if (receiveStatus == sf::Socket::Status::Disconnected)
        {
            std::cout << "\nClient disconnected" << std::endl;
            break;
        }
        else if (receiveStatus == sf::Socket::Status::Error)
        {
            std::cerr << "Error receiving data" << std::endl;
            break;
        }
        // NotReady is normal for non-blocking socket

        // Send response data back to client every second
        static auto lastSendTime = std::chrono::steady_clock::now();
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastSendTime).count();

        if (elapsed >= 1000)
        {
            PacketData responseData;
            responseData.sequenceNumber = sequenceNum++;

            // Server sends static position data
            responseData.position[0] = 0.0f;
            responseData.position[1] = 0.0f;
            responseData.position[2] = 0.0f;

            responseData.velocity[0] = 0.0f;
            responseData.velocity[1] = 0.0f;
            responseData.velocity[2] = 0.0f;

            responseData.status = 1; // Server active

            char msg[64];
            snprintf(msg, sizeof(msg), "Server response #%u", sequenceNum);
            responseData.setMessage(msg);

            auto now = std::chrono::system_clock::now();
            auto duration = now.time_since_epoch();
            responseData.timestamp = std::chrono::duration<double>(duration).count();

            // Send response
            if (client.send(&responseData, sizeof(responseData)) != sf::Socket::Status::Done)
            {
                std::cerr << "Error sending response packet" << std::endl;
            }
            else
            {
                packetsSent++;
                std::cout << "Sent response packet #" << sequenceNum << std::endl;
            }

            lastSendTime = currentTime;
        }

        // Small sleep to prevent busy waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    client.disconnect();
    listener.close();

    std::cout << "\nSession summary:" << std::endl;
    std::cout << "Packets sent: " << packetsSent << std::endl;
    std::cout << "Packets received: " << packetsReceived << std::endl;

    return 0;
}
*/
