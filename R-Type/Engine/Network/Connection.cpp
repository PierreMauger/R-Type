#include "Connection.hpp"

using namespace eng;

Connection::Connection(boost::asio::io_context &ioContext, std::shared_ptr<_QUEUE_TYPE> &dataInTcp, std::shared_ptr<_QUEUE_TYPE> &dataInUdp) : _ioContext(ioContext), _udpSocketIn(ioContext, _B_ASIO_UDP::endpoint(_B_ASIO_UDP::v4(), 0)), _udpSocketOut(ioContext), _tcpSocket(ioContext)
{
    this->_dataInTcp = dataInTcp;
    this->_dataInUdp = dataInUdp;
}

Connection::Connection(std::string ip, uint16_t portTcp, boost::asio::io_context &ioContext, std::shared_ptr<_QUEUE_TYPE> &dataInTcp, std::shared_ptr<_QUEUE_TYPE> &dataInUdp)
    : _ioContext(ioContext), _tcpEndpoint(boost::asio::ip::address::from_string(ip), portTcp), _udpSocketIn(ioContext, _B_ASIO_UDP::endpoint(_B_ASIO_UDP::v4(), 0)), _udpSocketOut(ioContext), _tcpSocket(ioContext)
{
    this->_dataInTcp = dataInTcp;
    this->_dataInUdp = dataInUdp;
}

Connection::~Connection()
{
    this->closeConnection();
}

void Connection::handleMsgTcp(const boost::system::error_code &error, size_t size)
{
    if (!this->checkConnection())
        return;
    if (!error) {
        std::cout << "[~] New TCP message from " << this->_tcpEndpoint << std::endl;
        if (size != _NET_BUFFER_SIZE)
            std::cout << "[?] TCP message size : " << size << std::endl;
        this->_dataInTcp->push_back(this->_tcpTmpBuffer);
    } else if (error == boost::asio::error::eof) {
        this->closeConnection();
        std::cout << "[-] Connection from " << this->_tcpEndpoint.address().to_string() << ":" << this->_tcpEndpoint.port() << " closed" << std::endl;
        return;
    } else {
        std::cerr << "[!] handleMsgTcp Error: " << error.message() << std::endl;
    }
    this->initConnection();
}

void Connection::handleMsgUdp(const boost::system::error_code &error, size_t size)
{
    if (!this->checkConnection())
        return;
    if (!error) {
        if (size != _NET_BUFFER_SIZE)
            std::cout << "[?] UDP message size : " << size << std::endl;
        this->_dataInUdp->push_back(this->_udpTmpBuffer);
    } else {
        std::cerr << "[!] handleMsgUdp Error: " << error.message() << std::endl;
    }
    this->initConnection();
}

void Connection::open()
{
    this->_udpSocketOut.open(_B_ASIO_UDP::v4());
    if (!this->_udpSocketOut.is_open())
        throw std::runtime_error("UDP socket can't be opened");
    std::cout << "[+] New connection from " << this->_tcpEndpoint.address().to_string() << ":" << this->_tcpEndpoint.port() << std::endl;
    this->initConnection();
}

void Connection::initConnection()
{
    if (!this->checkConnection())
        return;

    this->_tcpTmpBuffer.fill(0);
    this->_tcpSocket.async_receive(boost::asio::buffer(this->_tcpTmpBuffer), boost::bind(&Connection::handleMsgTcp, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

    this->_udpTmpBuffer.fill(0);
    this->_udpSocketIn.async_receive_from(boost::asio::buffer(this->_udpTmpBuffer), this->_tmpEndpoint, boost::bind(&Connection::handleMsgUdp, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

bool Connection::checkConnection()
{
    return this->_tcpSocket.is_open() && this->_udpSocketOut.is_open();
}

void Connection::run()
{
    this->_threadConnection = std::thread([this]() { this->open(); });
}

_B_ASIO_TCP::socket &Connection::getTcpSocket()
{
    return this->_tcpSocket;
}

_B_ASIO_UDP::socket &Connection::getUdpSocketIn()
{
    return this->_udpSocketIn;
}

_B_ASIO_UDP::socket &Connection::getUdpSocketOut()
{
    return this->_udpSocketOut;
}

bool Connection::isConnected()
{
    return this->_tcpSocket.is_open();
}

void Connection::closeConnection()
{
    if (this->_udpSocketOut.is_open())
        this->_udpSocketOut.close();
    if (this->_udpSocketIn.is_open())
        this->_udpSocketIn.close();
    if (this->_tcpSocket.is_open())
        this->_tcpSocket.close();
}

void Connection::setUdpEndpoint(std::string ip, uint16_t port)
{
    this->_udpEndpoint = _B_ASIO_UDP::endpoint(boost::asio::ip::address::from_string(ip), port);
}

void Connection::setTcpEndpoint(_B_ASIO_TCP::endpoint endpoint)
{
    this->_tcpEndpoint = endpoint;
}

_B_ASIO_UDP::endpoint Connection::getUdpEndpoint()
{
    return this->_udpEndpoint;
}

_B_ASIO_TCP::endpoint Connection::getTcpEndpoint()
{
    return this->_tcpEndpoint;
}

std::thread &Connection::getThreadConnection()
{
    return this->_threadConnection;
}

void Connection::tcpMsg(_STORAGE_DATA data)
{
    if (!this->checkConnection())
        return;
    this->_dataOutTcp.push_back(data);
}

void Connection::udpMsg(_STORAGE_DATA data)
{
    if (!this->checkConnection())
        return;
    this->_dataOutUdp.push_back(data);
}

void Connection::updateDataOut()
{
    if (!this->checkConnection())
        return;

    for (auto &data : this->_dataOutTcp) {
        this->_tcpSocket.send(boost::asio::buffer(data));
    }
    this->_dataOutTcp.clear();

    for (auto &data : this->_dataOutUdp) {
        this->_udpSocketOut.send_to(boost::asio::buffer(data), this->_udpEndpoint);
    }
    this->_dataOutUdp.clear();
}
