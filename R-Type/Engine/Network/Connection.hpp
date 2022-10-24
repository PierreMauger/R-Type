#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include "NetCommon.hpp"

namespace eng
{
    class Connection : public boost::enable_shared_from_this<Connection>
    {
        private:
            void handleMsgTcp(boost::system::error_code &error, size_t size);
            void handleMsgUdp(boost::system::error_code &error, size_t size);
            void open();
            void initConnection();

            boost::asio::io_context &_ioContext;
            _B_ASIO_UDP::endpoint _udpEndpoint;
            _B_ASIO_TCP::endpoint _tcpEndpoint;
            _B_ASIO_UDP::endpoint _tmpEndpoint;
            _B_ASIO_UDP::socket _udpSocketIn;
            _B_ASIO_UDP::socket _udpSocketOut;
            _B_ASIO_TCP::socket _tcpSocket;
            _QUEUE_TYPE &_dataIn;
            std::thread _threadConnection;
            _STORAGE_DATA _tcpTmpBuffer;
            _STORAGE_DATA _udpTmpBuffer;

        public:
            Connection(boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn);
            Connection(std::string ip, uint16_t portUdp, uint16_t portTcp, boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn);
            ~Connection();

            void run();
            bool isConnected();
            void closeConnection();

            std::thread &getThreadConnection();
            _B_ASIO_TCP::socket &getTcpSocket();
            _B_ASIO_UDP::socket &getUdpSocketIn();
            _B_ASIO_UDP::socket &getUdpSocketOut();

            void setUdpEndpoint(std::string ip, uint16_t port);
            void setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint);
            _B_ASIO_UDP::endpoint getUdpEndpoint();
            _B_ASIO_TCP::endpoint getTcpEndpoint();

            void tcpMsg(_STORAGE_DATA data);
            void udpMsg(_STORAGE_DATA data);
    };
} // namespace eng

#endif /* !CONNECTION_HPP_ */