#include "Connection.hpp"

Connection::Connection(boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket) :
    _ioContext(ioContext),
    _udpSocket(udpSocket),
    _tcpSocket(ioContext),
    _dataIn(dataIn)
{
}

Connection::Connection(std::string ip, uint16_t portUdp, uint16_t portTcp, boost::asio::io_context &ioContext, _QUEUE_TYPE &dataIn, _B_ASIO_UDP::socket &udpSocket) :
    _ioContext(ioContext),
    _udpEndpoint(boost::asio::ip::address::from_string(ip), portUdp),
    _tcpEndpoint(boost::asio::ip::address::from_string(ip), portTcp),
    _udpSocket(udpSocket),
    _tcpSocket(ioContext),
    _dataIn(dataIn)
{
}

Connection::~Connection()
{
}

void Connection::handleMsgTcp(boost::system::error_code error, _STORAGE_DATA buffer)
{
    if (!error) {
        std::cout << "New TCP message from " << this->_tcpEndpoint << std::endl;
        std::cout << "Message: " << buffer.data() << std::endl;
        this->_dataIn.push_back(buffer);
    } else {
        std::cerr << "handleMsgTcp Error: " << error.message() << std::endl;
    }
    this->initConnection();
}

void Connection::initConnection()
{
    _STORAGE_DATA buffer;
    this->_tcpSocket.async_receive(
        boost::asio::buffer(buffer),
        boost::bind(&Connection::handleMsgTcp,
                    this,
                    boost::asio::placeholders::error,
                    buffer
                )
    );
}

void Connection::run()
{
    this->initConnection();
}

_B_ASIO_TCP::socket &Connection::getTcpSocket()
{
    return this->_tcpSocket;
}

void Connection::setUdpEndpoint(std::string ip, uint16_t port)
{
    this->_udpEndpoint = _B_ASIO_UDP::endpoint(boost::asio::ip::address::from_string(ip), port);
}

_B_ASIO_UDP::endpoint Connection::getUdpEndpoint()
{
    return this->_udpEndpoint;
}

void Connection::setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint)
{
    this->_tcpEndpoint = endpoint;
}

_B_ASIO_TCP::endpoint Connection::getTcpEndpoint()
{
    return this->_tcpEndpoint;
}

void Connection::tcpMsg(_STORAGE_DATA data)
{
    this->_tcpSocket.send(boost::asio::buffer(data));
}

void Connection::udpMsg(_STORAGE_DATA data)
{
    this->_udpSocket.send_to(boost::asio::buffer(data), this->_udpEndpoint);
}