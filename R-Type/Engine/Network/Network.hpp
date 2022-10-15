#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "Includes.hpp"
#include "Engine/Network/Server/Server.hpp"
#include "Engine/Network/Client/Client.hpp"

namespace eng
{
    class Network
    {
        private:
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<Server> _server;
            std::shared_ptr<Client> _client;

        public:
            Network();
            ~Network() = default;
            void initServer(uint16_t portUdp, uint16_t portTcp);
            void initClient(std::string ip, uint16_t portUdp, uint16_t portTcp);
            std::shared_ptr<Server> getServer();
            std::shared_ptr<Client> getClient();
            std::shared_ptr<sf::Clock> getClock();
    };
} // namespace eng

#endif /* !NETWORK_HPP_ */