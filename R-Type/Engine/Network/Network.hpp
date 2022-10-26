#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "Engine/Network/Client/Client.hpp"
#include "Engine/Network/Serializer.hpp"
#include "Engine/Network/Server/Server.hpp"
#include "Includes.hpp"

namespace eng
{
    class Network
    {
        private:
            std::shared_ptr<Server> _server;
            std::shared_ptr<Client> _client;

            Serializer _serializer;

        public:
            Network();
            ~Network() = default;
            void initServer(uint16_t portTcp);
            void initClient(std::string ip, uint16_t portTcp);
            std::shared_ptr<Server> getServer();
            std::shared_ptr<Client> getClient();
            Serializer &getSerializer();
    };
} // namespace eng

#endif /* !NETWORK_HPP_ */
