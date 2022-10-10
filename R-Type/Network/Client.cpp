#include "Client.hpp"

Client::Client(std::string ip, uint16_t port) :
    _ioContext(),
    _resolver(_ioContext),
    _udpSocket(_ioContext, _B_ASIO_UDP::endpoint(boost::asio::ip::address::from_string(ip), port)),
    _dataIn(),
    _connection()
{
    this->_connection = boost::make_shared<Connection>(ip, port, this->_ioContext, this->_dataIn, this->_udpSocket);
    this->_connection->setTcpEndpoint(_B_ASIO_TCP::endpoint(boost::asio::ip::address::from_string(ip), port));
    this->_connection->setUdpEndpoint(ip, port);
}

Client::~Client()
{
    this->close();
    this->_ioContext.stop();
}

void Client::initClient()
{
    _STORAGE_DATA buffer;
    _B_ASIO_UDP::endpoint newEndpoint;
    this->_udpSocket.async_receive_from(
        boost::asio::buffer(buffer),
        newEndpoint,
        boost::bind(&Client::handleMsgUdp,
                    this,
                    boost::asio::placeholders::error,
                    buffer,
                    boost::asio::placeholders::bytes_transferred,
                    newEndpoint
                )
    );
}

void Client::run()
{
    try {
        this->initClient();
        this->_ioContext.run();
    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
}

void Client::open()
{
    _B_ASIO_TCP::resolver::results_type endpoints = this->_resolver.resolve(this->_connection->getTcpEndpoint());
    boost::asio::connect(this->_connection->getTcpSocket(), endpoints);
    this->_udpSocket.open(_B_ASIO_UDP::v4());
}

void Client::close()
{
    if (this->_udpSocket.is_open())
        this->_udpSocket.close();
    if (this->_connection->getTcpSocket().is_open())
        this->_connection->getTcpSocket().close();
}

void Client::handleMsgUdp(const boost::system::error_code &error, _STORAGE_DATA buffer, size_t size, _B_ASIO_UDP::endpoint newEndpoint)
{
    if (!error) {
        std::cout << "New UDP message from " << newEndpoint.address().to_string() << ":" << newEndpoint.port() << std::endl;
        std::cout << "Message: " << buffer.data() << std::endl;
        this->_dataIn.push_back(buffer);
    }
    this->initClient();
}

void Client::tcpMsg(_STORAGE_DATA data)
{
    this->_connection->tcpMsg(data);
}

void Client::udpMsg(_STORAGE_DATA data)
{
    this->_connection->udpMsg(data);
}

void Client::updateAction()
{
    if (!this->_dataIn.empty()) {
        _STORAGE_DATA data = this->_dataIn.front();
        this->_dataIn.erase(this->_dataIn.begin());
        std::cout << "New message: " << data.data() << std::endl;
    }
}