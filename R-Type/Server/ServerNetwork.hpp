/**
 * @file ServerNetwork.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The server network handling functions.
 * @copyright Epitech Rennes 2022
*/

#ifndef SERVERNETWORK_HPP_
#define SERVERNETWORK_HPP_

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
     * @brief The server network handling functions.
     * @class ServerNetwork
    */
    class ServerNetwork
    {
        private:
            void handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection);
            void initServerNetwork();

            boost::asio::io_context _ioContext;
            _B_ASIO_TCP::acceptor _acceptor;
            std::vector<boost::shared_ptr<Connection>> _listConnections;
            _QUEUE_TYPE _dataIn;
            _QUEUE_TYPE _dataOut;
            std::thread _threadContext;

        public:
            /**
             * @brief ServerNetwork constructor
             * @fn ServerNetwork(uint16_t portTcp)
             * @param portTcp The tcp port
            */
            ServerNetwork(uint16_t portTcp);
            /**
             * @brief ServerNetwork destructor
             * @fn ~ServerNetwork()
            */
            ~ServerNetwork();

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
            /**
             * @brief Get the connections
             * @fn std::vector<boost::shared_ptr<Connection>> &getConnections()
             * @return A reference to a vector of shared pointers of connections
            */
            std::vector<boost::shared_ptr<Connection>> &getConnections();
    };
} // namespace eng

#endif /* !SERVERNETWORK_HPP_ */