#include "Client/Client.hpp"

using namespace eng;

Client::Client(std::string ip, uint16_t portTcp) :
    _ioContext(),
    _resolver(_ioContext)
{
    this->_connection = boost::make_shared<Connection>(ip, portTcp, this->_ioContext, this->_dataIn);
    this->initClient();
}

Client::~Client()
{
    this->stop();
}

void Client::initClient()
{
    // Connect the Tcp socket
    _B_ASIO_TCP::resolver::results_type endpoints = this->_resolver.resolve(this->_connection->getTcpEndpoint());
    boost::asio::connect(this->_connection->getTcpSocket(), endpoints);
    if (this->_connection->getTcpSocket().is_open()) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "TCP socket is connected" << std::endl;
    } else
        throw std::runtime_error("TCP socket can't be connected");

    // Get the Udp port to send udp packet
    std::cout << "Wait to get the Udp OUT port to send udp packet" << std::endl;
    uint16_t portUdp = 0;
    this->_connection->getTcpSocket().read_some(boost::asio::buffer(&portUdp, sizeof(portUdp)));
    std::cout << "Udp OUT port is " << portUdp << std::endl;

    // Send the Udp port IN to the server
    std::cout << "Send the Udp port IN to the server" << std::endl;
    uint16_t newPortUdp = this->_connection->getUdpSocketIn().local_endpoint().port();
    std::cout << "Udp IN port is " << newPortUdp << std::endl;
    this->_connection->getTcpSocket().write_some(boost::asio::buffer(&newPortUdp, sizeof(newPortUdp)));

    // Link the server Udp socket
    std::cout << "Link the server Udp socket" << std::endl;
    this->_connection->setUdpEndpoint(this->_connection->getTcpEndpoint().address().to_string(), portUdp);

    // Run Connection
    std::cout << "Run Connection" << std::endl;
    this->_connection->run();
    std::cout << "----------------------------------------" << std::endl;
}

void Client::run()
{
    this->_threadContext = std::thread([this]() {
        this->_ioContext.run();
    });
}

void Client::stop()
{
    if (this->_connection->isConnected())
        this->_connection->closeConnection();
    if (this->_connection->getThreadConnection().joinable())
        this->_connection->getThreadConnection().join();
    if (!this->_ioContext.stopped())
        this->_ioContext.stop();
    if (this->_threadContext.joinable())
        this->_threadContext.join();
}

bool Client::isConnected()
{
    return this->_connection->isConnected();
}

void Client::tcpMsg(_STORAGE_DATA data)
{
    this->_connection->tcpMsg(data);
}

void Client::udpMsg(_STORAGE_DATA data)
{
    this->_connection->udpMsg(data);
}

_QUEUE_TYPE &Client::getQueueIn()
{
    return this->_dataIn;
}