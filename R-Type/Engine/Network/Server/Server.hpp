/**
 * @file Server.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The server handling functions.
 * @copyright Epitech Rennes 2022
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

/// @cond
#include "Connection.hpp"
#include "NetCommon.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The server handling functions.
     * @class Server
    */
    class Server
    {
        private:
            void handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection);
            void handleMsgUdp(const boost::system::error_code &error, _STORAGE_DATA buffer, size_t size);
            void initServer();

        protected:
            boost::asio::io_context _ioContext;
            _B_ASIO_UDP::socket _udpSocket;
            _B_ASIO_TCP::acceptor _acceptor;
            std::vector<boost::shared_ptr<Connection>> _listConnections;
            _QUEUE_TYPE _dataIn;
            std::thread _threadContext;
            _B_ASIO_UDP::endpoint _tmpEndpoint;

        public:
            /**
             * @brief Server constructor
             * @fn Server(uint16_t portUdp, uint16_t portTcp)
             * @param portUdp The udp port
             * @param portTdp The tdp port
            */
            Server(uint16_t portUdp, uint16_t portTcp);
            /**
             * @brief Server destructor
             * @fn ~Server()
            */
            ~Server();

            /**
             * @brief Run the server network.
             * @fn run()
            */
            void run();
            /**
             * @brief Stop the server network.
             * @fn stop()
            */
            void stop();

            /**
             * @brief Message the client with tcp.
             * @fn void tcpMsgCli(_B_ASIO_TCP::endpoint endpoint, _STORAGE_DATA data)
             * @param endpoint The tcp endpoint to send to.
             * @param data The data to send.
            */
            void tcpMsgCli(_B_ASIO_TCP::endpoint endpoint, _STORAGE_DATA data);
            /**
             * @brief Message the client with udp.
             * @fn void udpMsgCli(_B_ASIO_TCP::endpoint endpoint, _STORAGE_DATA data)
             * @param endpoint The udp endpoint to send to.
             * @param data The data to send.
            */
            void udpMsgCli(_B_ASIO_UDP::endpoint endpoint, _STORAGE_DATA data);

            /**
             * @brief Message the every client with tcp.
             * @fn void tcpMsgAll(_STORAGE_DATA data)
             * @param data The data to send.
            */
            void tcpMsgAll(_STORAGE_DATA data);
            /**
             * @brief Message the every client with udp.
             * @fn void udpMsgAll(_STORAGE_DATA data)
             * @param data The data to send.
            */
            void udpMsgAll(_STORAGE_DATA data);

            /**
             * @brief Close the connection to a client.
             * @fn void closeConnection(_B_ASIO_TCP::endpoint endpoint)
             * @param endpoint The endpoint of the client to close the connection to.
            */
            void closeConnection(_B_ASIO_TCP::endpoint endpoint);
            /**
             * @brief Update the connection to a client.
             * @fn void updateConnection()
            */
            void updateConnection();
    };
} // namespace eng

#endif /* !SERVER_HPP_ */