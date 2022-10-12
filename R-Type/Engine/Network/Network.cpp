#include "Network/Network.hpp"

eng::Network::Network()
{
}

eng::UDPClient &eng::Network::getUDPClient()
{
    return this->_client;
}
