#include "Network.hpp"

using namespace eng;

Network::Network()
{
}

void Network::initServer(uint16_t portUdp, uint16_t portTcp)
{
    this->_server = std::make_shared<Server>(portUdp, portTcp);
}

void Network::initClient(std::string ip, uint16_t portUdp, uint16_t portTcp)
{
    this->_client = std::make_shared<Client>(ip, portUdp, portTcp);
}

std::shared_ptr<Server> Network::getServer()
{
    return this->_server;
}

std::shared_ptr<Client> Network::getClient()
{
    return this->_client;
}

Serializer &Network::getSerializer()
{
    return this->_serializer;
}
