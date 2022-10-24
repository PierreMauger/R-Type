#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include "NetCommon.hpp"

namespace eng
{
    class Connection : public boost::enable_shared_from_this<Connection>
    {
        private:
            void handleMsgTcp(boost::system::error_code error, size_t size);
            void initConnection();

            boost::asio::io_context &_ioContext;
            _B_ASIO_UDP::endpoint _udpEndpoint;
            _B_ASIO_TCP::endpoint _tcpEndpoint;
            _B_ASIO_UDP::socket &_udpSocket;
            _B_ASIO_TCP::socket _tcpSocket;
            _QUEUE_TYPE &_dataIn;
            std::thread _threadConnection;
            _STORAGE_DATA _tcpTmpBuffer;

        public:
            Connection(boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket);
            Connection(std::string ip, uint16_t portUdp, uint16_t portTcp, boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket);
            ~Connection();

            void run();
            _B_ASIO_TCP::socket &getTcpSocket();
            bool isConnected();
            void closeConnection();

            void setUdpEndpoint(std::string ip, uint16_t port);
            void setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint);
            _B_ASIO_UDP::endpoint getUdpEndpoint();
            _B_ASIO_TCP::endpoint getTcpEndpoint();
            std::thread &getThreadConnection();

            void tcpMsg(_STORAGE_DATA data);
            void udpMsg(_STORAGE_DATA data);
    };
} // namespace eng

#endif /* !CONNECTION_HPP_ */
