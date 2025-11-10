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
    std::unique_ptr<sf::TcpSocket> socket_ = std::make_unique<sf::TcpSocket>();
};
