#include "Client.hpp"

Client::Client(boost::asio::io_context &ioContext, std::string ip, uint16_t portUdp, uint16_t portTcp) :
    _ioContext(ioContext),
    _resolver(_ioContext),
    _udpSocket(_ioContext),
    _dataIn(),
    _connection()
{
    if ((portUdp == portTcp) || (portUdp > 65535) || (portTcp > 65535))
        throw std::runtime_error("Invalid port, must be different and between 0 and 65535");
    this->_connection = boost::make_shared<Connection>(ip, portUdp, portTcp, this->_ioContext, this->_dataIn, this->_udpSocket);
    this->_connection->setTcpEndpoint(_B_ASIO_TCP::endpoint(boost::asio::ip::address::from_string(ip), portTcp));
    this->_connection->setUdpEndpoint(ip, portUdp);
    this->open();
}

Client::~Client()
{
    this->close();
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

void Client::open()
{
    _B_ASIO_TCP::resolver::results_type endpoints = this->_resolver.resolve(this->_connection->getTcpEndpoint());
    boost::asio::connect(this->_connection->getTcpSocket(), endpoints);
    this->_udpSocket.open(_B_ASIO_UDP::v4());
    // this->tcpMsg({'H', 'E', 'L', 'L', 'O'});
    this->initClient();
}

void Client::close()
{
    if (this->_udpSocket.is_open())
        this->_udpSocket.close();
    if (this->_connection->getTcpSocket().is_open())
        this->_connection->getTcpSocket().close();
    if (!this->_ioContext.stopped())
        this->_ioContext.stop();
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
    std::cout << "Sending UDP message" << std::endl;
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