#include "PacketData.h"
#include "SFML/Network.hpp"
#include <fstream>
#include <iostream>
#include <memory>

class Server
{
  public:
    Server(const int port);
    void listen();
    void writeToLog(const std::string &msg);

    bool running_{true};

  private:
    int port_;
    std::shared_ptr<sf::TcpListener> listener_;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;
};
