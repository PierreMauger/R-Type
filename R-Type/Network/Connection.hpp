#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include "NetCommon.hpp"

class Connection : public boost::enable_shared_from_this<Connection>
{
    protected:
        boost::asio::io_context &_ioContext;
        _B_ASIO_UDP::endpoint _udpEndpoint;
        _B_ASIO_TCP::endpoint _tcpEndpoint;
        _B_ASIO_UDP::socket &_udpSocket;
        _B_ASIO_TCP::socket _tcpSocket;
        _QUEUE_TYPE &_dataIn;

    public:
        Connection(boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket);
        Connection(std::string ip, uint16_t port, boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket);
        ~Connection();
        _B_ASIO_TCP::socket &getTcpSocket();
        void initConnection();
        void setUdpEndpoint(std::string ip, uint16_t port);
        void setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint);
        _B_ASIO_UDP::endpoint getUdpEndpoint();
        _B_ASIO_TCP::endpoint getTcpEndpoint();
        void handleMsgTcp(boost::system::error_code error, _STORAGE_DATA buffer);
        void tcpMsg(_STORAGE_DATA data);
        void udpMsg(_STORAGE_DATA data);
};

#endif /* !CONNECTION_HPP_ */