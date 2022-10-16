/**
 * @file Client.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The client handling functions.
 * @copyright Epitech Rennes 2022
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

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
     * @brief The client handling functions.
     * @class Client
    */
    class Client
    {
        private:
            void handleMsgUdp(const boost::system::error_code &error, _STORAGE_DATA buffer, size_t size, _B_ASIO_UDP::endpoint newEndpoint);
            void initClient();
            void open();

        protected:
            boost::asio::io_context _ioContext;
            _B_ASIO_TCP::resolver _resolver;
            _B_ASIO_UDP::socket _udpSocket;
            boost::shared_ptr<Connection> _connection;
            _QUEUE_TYPE _dataIn;
            std::thread _threadContext;

        public:
            /**
             * @brief Client constructor
             * @fn Client(std::string ip, uint16_t portUdp, uint16_t portTcp)
             * @param ip The ip of the client
             * @param portUdp The udp port
             * @param portTdp The tdp port
            */
            Client(std::string ip, uint16_t portUdp, uint16_t portTcp);
            /**
             * @brief Client destructor
             * @fn ~Client()
            */
            ~Client();

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
             * @brief Send a tcp message to the server.
             * @fn void tcpMsg(_STORAGE_DATA data)
             * @param data The data to send.
            */
            void tcpMsg(_STORAGE_DATA data);
            /**
             * @brief Send a udp message to the server.
             * @fn void udpMsg(_STORAGE_DATA data)
             * @param data The data to send.
            */
            void udpMsg(_STORAGE_DATA data);
    };
} // namespace eng

#endif /* !CLIENT_HPP_ */