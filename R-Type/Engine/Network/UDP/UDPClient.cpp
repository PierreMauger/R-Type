#include "Engine/Network/UDP/UDPClient.hpp"

eng::UDPClient::UDPClient()
{
}

eng::EntitySerializer &eng::UDPClient::getSerializer()
{
    return this->_serializer;
}
