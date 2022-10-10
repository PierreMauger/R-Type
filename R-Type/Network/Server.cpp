#include "Server.hpp"

Server::Server(uint16_t port) :
    _ioContext(),
    _udpSocket(_ioContext, _B_ASIO_UDP::endpoint(_B_ASIO_UDP::v4(), port)),
    _acceptor(_ioContext, _B_ASIO_TCP::endpoint(_B_ASIO_TCP::v4(), port))
{
}

Server::~Server()
{
    if (this->_udpSocket.is_open())
        this->_udpSocket.close();
    for (auto &connection : this->_listConnections)
        if (connection->getTcpSocket().is_open())
            connection->getTcpSocket().close();
    this->_ioContext.stop();
}

void Server::initServer()
{
    _STORAGE_DATA buffer;
    _B_ASIO_UDP::endpoint newEndpoint;
    this->_udpSocket.async_receive_from(
        boost::asio::buffer(buffer),
        newEndpoint,
        boost::bind(&Server::handleMsgUdp,
                    this,
                    boost::asio::placeholders::error,
                    buffer,
                    boost::asio::placeholders::bytes_transferred,
                    newEndpoint
                )
    );

    boost::shared_ptr<Connection> newConnection = boost::make_shared<Connection>(this->_ioContext, this->_dataIn, this->_udpSocket);
    this->_acceptor.async_accept(newConnection->getTcpSocket(),
        boost::bind(&Server::handleNewTcp,
                    this,
                    boost::asio::placeholders::error,
                    newConnection
                )
    );
}

void Server::run()
{
    try {
        this->initServer();
        this->_ioContext.run();
    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
}

void Server::handleMsgUdp(const boost::system::error_code &error, _STORAGE_DATA buffer, size_t size, _B_ASIO_UDP::endpoint newEndpoint)
{
    if (!error) {
        std::cout << "New UDP message from " << newEndpoint.address().to_string() << ":" << newEndpoint.port() << std::endl;
        std::cout << "Message: " << buffer.data() << std::endl;
        this->_dataIn.push_back(buffer);
    }
    this->initServer();
}

void Server::handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection)
{
    if (!error) {
        newConnection->setTcpEndpoint(newConnection->getTcpSocket().remote_endpoint());
        std::string ip = newConnection->getTcpEndpoint().address().to_string();
        uint16_t port = newConnection->getTcpEndpoint().port();
        newConnection->setUdpEndpoint(ip, port);
        std::cout << "New TCP connection from " << ip << ":" << port << std::endl;
    }
    this->initServer();
}

void Server::tcpMsgCli(_B_ASIO_TCP::endpoint endpoint, _STORAGE_DATA data)
{
    for (auto &connection : this->_listConnections) {
        if (connection->getTcpEndpoint() == endpoint) {
            connection->tcpMsg(data);
            break;
        } else {
            std::cout << "Client not found" << std::endl;
        }
    }
}

void Server::udpMsgCli(_B_ASIO_UDP::endpoint endpoint, _STORAGE_DATA data)
{
    for (auto &connection : this->_listConnections) {
        if (connection->getUdpEndpoint() == endpoint) {
            connection->udpMsg(data);
            break;
        } else {
            std::cout << "Client not found" << std::endl;
        }
    }
}

void Server::tcpMsgAll(_STORAGE_DATA data)
{
    for (auto &connection : this->_listConnections) {
        connection->tcpMsg(data);
    }
}

void Server::udpMsgAll(_STORAGE_DATA data)
{
    for (auto &connection : this->_listConnections) {
        connection->udpMsg(data);
    }
}

void Server::newConnect(_B_ASIO_TCP::endpoint endpoint)
{
    std::cout << "New TCP connection from " << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;
}

void Server::updateAction()
{
    if (!this->_dataIn.empty()) {
        _STORAGE_DATA data = this->_dataIn.front();
        this->_dataIn.erase(this->_dataIn.begin());
        std::cout << "New message: " << data.data() << std::endl;
    }
}