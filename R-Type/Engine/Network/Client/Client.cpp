#include "Client/Client.hpp"

using namespace eng;

Client::Client(std::string ip, uint16_t portUdp, uint16_t portTcp) :
    _ioContext(),
    _resolver(_ioContext),
    _udpSocket(_ioContext)
{
    if (portUdp == portTcp)
        throw std::runtime_error("Invalid port, must be different and between 0 and 65535");
    this->_connection = boost::make_shared<Connection>(ip, portUdp, portTcp, this->_ioContext, this->_dataIn, this->_udpSocket);
    this->_connection->setTcpEndpoint(_B_ASIO_TCP::endpoint(boost::asio::ip::address::from_string(ip), portTcp));
    this->_connection->setUdpEndpoint(ip, portUdp);
}

Client::~Client()
{
    this->stop();
}

void Client::initClient()
{
    this->_udpTmpBuffer.fill(0);
    this->_udpSocket.async_receive_from(
        boost::asio::buffer(this->_udpTmpBuffer),
        this->_tmpEndpoint,
        boost::bind(&Client::handleMsgUdp,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                )
    );
}

void Client::open()
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
    this->initClient();
}

void Client::run()
{
    this->open();
    this->_threadContext = std::thread([this]() {
        this->_ioContext.run();
    });
}

void Client::stop()
{
    if (this->_udpSocket.is_open())
        this->_udpSocket.close();
    if (this->_connection->getTcpSocket().is_open())
        this->_connection->getTcpSocket().close();
    // if (this->_connection->getThreadConnection().joinable())
        // this->_connection->getThreadConnection().join();
    if (!this->_ioContext.stopped())
        this->_ioContext.stop();
    if (this->_threadContext.joinable())
        this->_threadContext.join();
}

void Client::handleMsgUdp(const boost::system::error_code &error, size_t size)
{
    if (!error) {
        std::cout << "New UDP message from " << this->_tmpEndpoint.address().to_string() << ":" << this->_tmpEndpoint.port() << std::endl;
        std::cout << "Message Size: " << size << std::endl;
        this->_dataIn.push_back(this->_udpTmpBuffer);
    } else {
        std::cerr << "handleMsgUdp Error: " << error.message() << std::endl;
    }
    this->initClient();
}

void Client::tcpMsg(_STORAGE_DATA data)
{
    std::cout << "Sending TCP message" << std::endl;
    this->_connection->tcpMsg(data);
}

void Client::udpMsg(_STORAGE_DATA data)
{
    std::cout << "Sending UDP message" << std::endl;
    this->_connection->udpMsg(data);
}

_QUEUE_TYPE &Client::getQueueIn()
{
    return this->_dataIn;
}

_QUEUE_TYPE &Client::getQueueOut()
{
    return this->_dataOut;
}