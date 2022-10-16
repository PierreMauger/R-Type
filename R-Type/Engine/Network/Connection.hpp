/**
 * @file Connection.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The network's connection.
 * @copyright Epitech Rennes 2022
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

/// @cond
#include "NetCommon.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The network's connection.
     * @class Connection
    */
    class Connection : public boost::enable_shared_from_this<Connection>
    {
        private:
            void handleMsgTcp(boost::system::error_code error, _STORAGE_DATA buffer);
            void initConnection();

        protected:
            boost::asio::io_context &_ioContext;
            _B_ASIO_UDP::endpoint _udpEndpoint;
            _B_ASIO_TCP::endpoint _tcpEndpoint;
            _B_ASIO_UDP::socket &_udpSocket;
            _B_ASIO_TCP::socket _tcpSocket;
            _QUEUE_TYPE &_dataIn;
            std::thread _threadConnection;

        public:
            /**
             * @brief Connection constructor.
             * @fn Connection(boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket)
             * @param ioContext A reference to the input output context.
             * @param dataIn A reference to the input data.
             * @param udpSocket A reference to the udp socket. 
            */
            Connection(boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket);
            /**
             * @brief Connection constructor.
             * @fn Connection(std::string ip, uint16_t portUdp, uint16_t portTcp, boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket)
             * @param ip The ip of the client.
             * @param portUdp The udp port.
             * @param portTcp The tcp port.
             * @param ioContext A reference to the input output context.
             * @param dataIn A reference to the input data.
             * @param udpSocket A reference to the udp socket. 
            */
            Connection(std::string ip, uint16_t portUdp, uint16_t portTcp, boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket);
            /**
             * @brief Connection destructor.
             * @fn ~Connection()
            */
            ~Connection();

            /**
             * @brief Run the connection.
             * @fn run()
            */
            void run();
            /**
             * @brief Get the tcp socket.
             * @fn _B_ASIO_TCP::socket &getTcpSocket()
             * @return A reference to the tcp socket
            */
            _B_ASIO_TCP::socket &getTcpSocket();
            /**
             * @brief Check if the client is connected.
             * @fn bool isConnected()
             * @return A boolean indicating if the client is connect or not.
            */
            bool isConnected();
            /**
             * @brief Close the connection.
             * @fn void closeConnection()
            */
            void closeConnection();

            /**
             * @brief Set the udp endpoint.
             * @fn void setUdpEndpoint(std::string ip, uint16_t port)
             * @param ip The client ip.
             * @param port The client port.
            */
            void setUdpEndpoint(std::string ip, uint16_t port);
            /**
             * @brief Set the tdp endpoint.
             * @fn void setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint)
             * @param endpoint The endpoint to set.
            */
            void setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint);
            /**
             * @brief Get the udp endpoint.
             * @fn _B_ASIO_UDP::endpoint getUdpEndpoint()
             * @return The udp endpoint.
            */
            _B_ASIO_UDP::endpoint getUdpEndpoint();
            /**
             * @brief Get the tdp endpoint.
             * @fn _B_ASIO_TCP::endpoint getTcpEndpoint()
             * @return The tdp endpoint.
            */
            _B_ASIO_TCP::endpoint getTcpEndpoint();
            /**
             * @brief Get the thread connection.
             * @fn std::thread &getThreadConnection()
             * @return A reference to the thread connection.
            */
            std::thread &getThreadConnection();

            /**
             * @brief Send a tcp message.
             * @fn void tcpMsg(_STORAGE_DATA data)
             * @param data The data to send through tcp connection.
            */
            void tcpMsg(_STORAGE_DATA data);
            /**
             * @brief Send an ucp message.
             * @fn void udpMsg(_STORAGE_DATA data)
             * @param data The data to send through udp connection.
            */
            void udpMsg(_STORAGE_DATA data);
    };
} // namespace eng

#endif /* !CONNECTION_HPP_ */