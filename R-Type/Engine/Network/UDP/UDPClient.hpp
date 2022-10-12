#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include "Engine/Network/UDP/EntitySerializer.hpp"
#include "Includes.hpp"

namespace eng
{
    class UDPClient
    {
        private:
            EntitySerializer _serializer;

        public:
            UDPClient();
            ~UDPClient() = default;

            EntitySerializer &getSerializer();
    };
}

#endif // UDPCLIENT_HPP
