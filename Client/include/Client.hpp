#include "SFML/Network.hpp"
#include <iostream>
#include <string>

class Client
{
  public:
    Client(const int port);
    void promptMessage();

  private:
    int port_;
};
