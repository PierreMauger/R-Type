#include "Network.hpp"

using namespace eng;

Network::Network()
{
    this->_clock = std::make_shared<sf::Clock>();
    // this->_server = std::make_shared<Server>();
    // this->_client = std::make_shared<Client>();
}

std::shared_ptr<sf::Clock> Network::getClock()
{
    return this->_clock;
}

std::shared_ptr<Server> Network::getServer()
{
    return this->_server;
}

std::shared_ptr<Client> Network::getClient()
{
    return this->_client;
}