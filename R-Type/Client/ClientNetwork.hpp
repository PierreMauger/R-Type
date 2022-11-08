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
            std::shared_ptr<_QUEUE_TYPE> _dataInTcp;
            std::shared_ptr<_QUEUE_TYPE> _dataInUdp;
            std::shared_ptr<Connection> _connection;
            std::thread _threadContext;

            std::time_t _time;

        public:
            /**
             * @brief ClientNetwork constructor
             * @fn ClientNetwork()
             */
            ClientNetwork();
            /**
             * @brief ClientNetwork destructor
             * @fn ~ClientNetwork()
             */
            ~ClientNetwork();

            /**
             * @brief Start the client network.
             * @fn void start(std::string ip, uint16_t portTcp)
             * @param ip The server ip.
             * @param portTcp The server tcp port.
             */
            void start(std::string ip, uint16_t portTcp);
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
             * @fn _QUEUE_TYPE &getQueueInTcp()
             * @return A reference to the tcp input queue
             */
            _QUEUE_TYPE &getQueueInTcp();
            /**
             * @brief Get the input queue
             * @fn _QUEUE_TYPE &getQueueInUdp()
             * @return A reference to the udp input queue
             */
            _QUEUE_TYPE &getQueueInUdp();

            /**
             * @brief Update the client network
             * @fn void update()
             */
            void updateConnection();

            /**
             * @brief Get the time
             * @fn st::size_t getTime()
             * @return The time
             */
            std::time_t getTime();
    };
} // namespace eng

#endif /* !CLIENTNETWORK_HPP_ */
