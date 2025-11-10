#include "PacketData.h"
#include "SFML/Network.hpp"
#include <chrono>
#include <iostream>
#include <string>

class Client
{
  public:
    Client(const int port);
    void promptMessage();
    void sendMessage(const std::string &msg);

  private:
    int port_;
    uint32_t sequenceNum_{0};
    uint32_t packetsSent{0};
    uint32_t packetsReceived{0};
    std::unique_ptr<sf::TcpSocket> socket_ = std::make_unique<sf::TcpSocket>();
};
