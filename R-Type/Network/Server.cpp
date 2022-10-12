#include "Server.hpp"

Server::Server(uint16_t portUdp, uint16_t portTcp) :
    _ioContext(),
    _udpSocket(_ioContext, _B_ASIO_UDP::endpoint(_B_ASIO_UDP::v4(), portUdp)),
    _acceptor(_ioContext, _B_ASIO_TCP::endpoint(_B_ASIO_TCP::v4(), portTcp)),
    _threadContext()
{
    if ((portUdp == portTcp) || (portUdp > 65535) || (portTcp > 65535))
        throw std::runtime_error("Invalid port, must be different and between 0 and 65535");
    this->initServer();
}

Server::~Server()
{
    this->stop();
}

void Server::initServer()
{
    std::cout << "initServer..";
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
    std::cout << "done" << std::endl;
}

bool Server::isConnected(boost::shared_ptr<Connection> client)
{
    if (client->getTcpSocket().is_open())
        return true;
    return false;
}

void Server::run()
{
    std::cout << "run..";
    this->_threadContext = std::thread([this]() {
        this->_ioContext.run();
    });
    std::cout << "done" << std::endl;
}

void Server::stop()
{
    if (this->_udpSocket.is_open())
        this->_udpSocket.close();
    for (auto &connection : this->_listConnections)
        if (connection->getTcpSocket().is_open())
            connection->getTcpSocket().close();
    if (!this->_ioContext.stopped())
        this->_ioContext.stop();
    if (this->_threadContext.joinable())
        this->_threadContext.join();
}

void Server::handleMsgUdp(const boost::system::error_code &error, _STORAGE_DATA buffer, size_t size, _B_ASIO_UDP::endpoint newEndpoint)
{
    std::cout << "handleMsgUdp..";
    if (!error) {
        std::cout << "New UDP message from " << newEndpoint.address().to_string() << ":" << newEndpoint.port() << std::endl;
        std::cout << "Message: " << buffer.data() << std::endl;
        this->_dataIn.push_back(buffer);
    } else {
        std::cerr << "handleMsgUdp Error: " << error.message() << std::endl;
    }
    std::cout << "done" << std::endl;
    this->initServer();
}

void Server::handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection)
{
    std::cout << "handleNewTcp..";
    if (!error) {
        newConnection->setTcpEndpoint(newConnection->getTcpSocket().remote_endpoint());
        std::string ip = newConnection->getTcpEndpoint().address().to_string();
        uint16_t port = newConnection->getTcpEndpoint().port();
        newConnection->setUdpEndpoint(ip, port);
        std::cout << "New TCP connection from " << ip << ":" << port << std::endl;
        newConnection->run();
        this->_listConnections.push_back(newConnection);
    } else {
        std::cerr << "handleNewTcp Error: " << error.message() << std::endl;
    }
    std::cout << "done" << std::endl;
    this->initServer();
}

void Server::tcpMsgCli(_B_ASIO_TCP::endpoint endpoint, _STORAGE_DATA data)
{
    for (auto &connection : this->_listConnections) {
        if (connection->getTcpEndpoint() == endpoint) {
            connection->tcpMsg(data);
            break;
        } else {
            std::cerr << "Client not found" << std::endl;
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
            std::cerr << "Client not found" << std::endl;
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