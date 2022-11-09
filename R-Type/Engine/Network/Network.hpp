/**
 * @file Network.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The engine's network.
 * @copyright Epitech Rennes 2022
 */

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

/// @cond
#include "Engine/Network/Client/Client.hpp"
#include "Engine/Network/Serializer.hpp"
#include "Engine/Network/Server/Server.hpp"
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The engine's network.
     * @class Network
     */
    class Network
    {
        private:
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<Server> _server;
            std::shared_ptr<Client> _client;

            Serializer _serializer;

        public:
            /**
             * @brief Network constructor.
             * @fn Network()
             */
            Network();
            /**
             * @brief Network destructor.
             * @fn ~Network()
             */
            ~Network() = default;
            /**
             * @brief Initialize the server.
             * @fn void initServer(uint16_t portUdp, uint16_t portTcp)
             * @param portUdp The port for the UDP connection.
             * @param portTdp The port for the TDP connection.
             */
            void initServer(uint16_t portUdp, uint16_t portTcp);
            /**
             * @brief Initialize the client.
             * @fn void initClient(std::string ip, uint16_t portUdp, uint16_t portTcp)
             * @param ip The ip of the client.
             * @param portUdp The port for the UDP connection.
             * @param portTdp The port for the TDP connection.
             */
            void initClient(std::string ip, uint16_t portUdp, uint16_t portTcp);
            /**
             * @brief Get the server
             * @fn std::shared_ptr<Server> getServer()
             * @return A shared pointer to the server.
             */
            std::shared_ptr<Server> getServer();
            /**
             * @brief Get the client
             * @fn std::shared_ptr<Client> getClient()
             * @return A shared pointer to the client.
             */
            std::shared_ptr<Client> getClient();
            /**
             * @brief Get the clock
             * @fn std::shared_ptr<sf::Clock> getClock()
             * @return A shared pointer to the clock.
             */
            std::shared_ptr<sf::Clock> getClock();
            /**
             * @brief Get the serializer
             * @fn Serializer &getSerializer()
             * @return A reference to the serializer.
             */
            Serializer &getSerializer();
    };
} // namespace eng

#endif /* !NETWORK_HPP_ */
