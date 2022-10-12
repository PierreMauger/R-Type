#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "Engine/Network/UDP/UDPClient.hpp"
#include "Includes.hpp"

namespace eng
{
    class Network
    {
        private:
            // add tcp
            UDPClient _client;

        public:
            Network();
            ~Network() = default;

            UDPClient &getUDPClient();
    };
}

#endif // NETWORK_HPP
