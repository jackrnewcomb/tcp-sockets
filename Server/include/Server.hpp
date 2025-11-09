#include "SFML/Network.hpp"
#include <iostream>
#include <memory>

class Server
{
  public:
    Server(const int port);
    void listen();
    void writeLog();

  private:
    int port_;
    std::shared_ptr<sf::TcpListener> listener_;
};
