#include "ClientNetwork.hpp"

using namespace eng;

ClientNetwork::ClientNetwork(std::string ip, uint16_t portUdp, uint16_t portTcp) : _ioContext(), _resolver(_ioContext), _udpSocket(_ioContext)
{
    if (portUdp == portTcp)
        throw std::runtime_error("Invalid port, must be different and between 0 and 65535");
    this->_connection = boost::make_shared<Connection>(ip, portUdp, portTcp, this->_ioContext, this->_dataIn, this->_udpSocket);
    this->_connection->setTcpEndpoint(_B_ASIO_TCP::endpoint(boost::asio::ip::address::from_string(ip), portTcp));
    this->_connection->setUdpEndpoint(ip, portUdp);
}

ClientNetwork::~ClientNetwork()
{
    this->stop();
}

void ClientNetwork::initClientNetwork()
{
    this->_udpTmpBuffer.fill(0);
    this->_udpSocket.async_receive_from(boost::asio::buffer(this->_udpTmpBuffer), this->_tmpEndpoint,
                                        boost::bind(&ClientNetwork::handleMsgUdp, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void ClientNetwork::open()
{
    // Connect the Tcp socket
    _B_ASIO_TCP::resolver::results_type endpoints = this->_resolver.resolve(this->_connection->getTcpEndpoint());
    boost::asio::connect(this->_connection->getTcpSocket(), endpoints);
    if (this->_connection->getTcpSocket().is_open())
        std::cout << "TCP socket is connected" << std::endl;
    else
        throw std::runtime_error("TCP socket can't be connected");

    // Open the Udp socket
    this->_udpSocket.open(_B_ASIO_UDP::v4());
    if (this->_udpSocket.is_open())
        std::cout << "UDP socket is opened" << std::endl;
    else
        throw std::runtime_error("UDP socket can't be opened");
    this->_connection->run();
    this->initClientNetwork();
}

void ClientNetwork::run()
{
    this->open();
    this->_threadContext = std::thread([this]() { this->_ioContext.run(); });
}

void ClientNetwork::stop()
{
    if (this->_udpSocket.is_open())
        this->_udpSocket.close();
    if (this->_connection->isConnected())
        this->_connection->closeConnection();
    if (this->_connection->getThreadConnection().joinable())
        this->_connection->getThreadConnection().join();
    if (!this->_ioContext.stopped())
        this->_ioContext.stop();
    if (this->_threadContext.joinable())
        this->_threadContext.join();
}

bool ClientNetwork::isConnected()
{
    return this->_connection->isConnected();
}

void ClientNetwork::handleMsgUdp(const boost::system::error_code &error, size_t size)
{
    if (!error) {
        std::cout << "New UDP message from " << this->_tmpEndpoint.address().to_string() << ":" << this->_tmpEndpoint.port() << std::endl;
        if (size != _NET_BUFFER_SIZE)
            std::cout << "Invalid UDP message size : " << size << std::endl;
        this->_dataIn.push_back(this->_udpTmpBuffer);
    } else {
        std::cerr << "handleMsgUdp Error: " << error.message() << std::endl;
    }
    this->initClientNetwork();
}

void ClientNetwork::tcpMsg(_STORAGE_DATA data)
{
    std::cout << "Sending TCP message" << std::endl;
    this->_connection->tcpMsg(data);
}

void ClientNetwork::udpMsg(_STORAGE_DATA data)
{
    std::cout << "Sending UDP message" << std::endl;
    this->_connection->udpMsg(data);
}

_QUEUE_TYPE &ClientNetwork::getQueueIn()
{
    return this->_dataIn;
}

_QUEUE_TYPE &ClientNetwork::getQueueOut()
{
    return this->_dataOut;
}
