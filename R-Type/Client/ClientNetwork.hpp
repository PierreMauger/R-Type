/**
 * @file ClientNetwork.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The client network handling functions.
 * @copyright Epitech Rennes 2022
 */

#ifndef CLIENTNETWORK_HPP_
#define CLIENTNETWORK_HPP_

/// @cond
#include "Connection.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The client network handling functions.
     * @class ClientNetwork
     */
    class ClientNetwork
    {
        private:
            void initClientNetwork();
            void open();

            boost::asio::io_context _ioContext;
            _B_ASIO_TCP::resolver _resolver;
            std::shared_ptr<Connection> _connection;
            _QUEUE_TYPE _dataIn;
            std::thread _threadContext;

        public:
            /**
             * @brief ClientNetwork constructor
             * @fn ClientNetwork(std::string ip, uint16_t portTcp)
             * @param ip The ip of the client
             * @param portTdp The tdp port
             */
            ClientNetwork(std::string ip, uint16_t portTcp);
            /**
             * @brief ClientNetwork destructor
             * @fn ~ClientNetwork()
             */
            ~ClientNetwork();

            /**
             * @brief Run the client network
             * @fn void run()
             */
            void run();
            /**
             * @brief Stop the client network
             * @fn void stop()
             */
            void stop();
            /**
             * @brief Check if the client is connected
             * @fn bool isConnected()
             * @return The boolean indicating if the client is connected
             */
            bool isConnected();

            /**
             * @brief Send a tcp message to the server.
             * @fn void tcpMsg(_STORAGE_DATA data)
             * @param data The data to send.
             */
            void tcpMsg(_STORAGE_DATA data);
            /**
             * @brief Send an udp message to the server.
             * @fn void udpMsg(_STORAGE_DATA data)
             * @param data The data to send.
             */
            void udpMsg(_STORAGE_DATA data);

            /**
             * @brief Get the input queue
             * @fn _QUEUE_TYPE &getQueueIn()
             * @return A reference to the input queue
             */
            _QUEUE_TYPE &getQueueIn();
            /**
             * @brief Get the output queue
             * @fn _QUEUE_TYPE &getQueueOut()
             * @return A reference to the output queue
             */
            _QUEUE_TYPE &getQueueOut();
    };
} // namespace eng

#endif /* !CLIENTNETWORK_HPP_ */
