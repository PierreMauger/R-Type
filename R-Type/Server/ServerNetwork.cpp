#include "ServerNetwork.hpp"

using namespace eng;

ServerNetwork::ServerNetwork(uint16_t portUdp, uint16_t portTcp)
    : _ioContext(), _udpSocket(_ioContext, _B_ASIO_UDP::endpoint(_B_ASIO_UDP::v4(), portUdp)), _acceptor(_ioContext, _B_ASIO_TCP::endpoint(_B_ASIO_TCP::v4(), portTcp))
{
    if (portUdp == portTcp)
        throw std::runtime_error("Invalid port, must be different and between 0 and 65535");
    this->initServerNetwork();
}

ServerNetwork::~ServerNetwork()
{
    this->stop();
}

void ServerNetwork::initServerNetwork()
{
    this->_udpTmpBuffer.fill(0);
    this->_udpSocket.async_receive_from(boost::asio::buffer(this->_udpTmpBuffer), this->_tmpEndpoint,
                                        boost::bind(&ServerNetwork::handleMsgUdp, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

    boost::shared_ptr<Connection> newConnection = boost::make_shared<Connection>(this->_ioContext, this->_dataIn, this->_udpSocket);
    this->_acceptor.async_accept(newConnection->getTcpSocket(), boost::bind(&ServerNetwork::handleNewTcp, this, boost::asio::placeholders::error, newConnection));
}

void ServerNetwork::run()
{
    this->_threadContext = std::thread([this]() { this->_ioContext.run(); });
    std::cout << "Server is running" << std::endl;
}

void ServerNetwork::stop()
{
    if (this->_udpSocket.is_open())
        this->_udpSocket.close();
    for (auto &connection : this->_listConnections) {
        if (connection->isConnected())
            connection->closeConnection();
        if (connection->getThreadConnection().joinable())
            connection->getThreadConnection().join();
    }
    this->_listConnections.clear();

    if (!this->_ioContext.stopped())
        this->_ioContext.stop();
    if (this->_threadContext.joinable())
        this->_threadContext.join();
}

void ServerNetwork::handleMsgUdp(const boost::system::error_code &error, size_t size)
{
    if (!error) {
        std::cout << "New UDP message from " << this->_tmpEndpoint.address().to_string() << ":" << this->_tmpEndpoint.port() << std::endl;
        if (size != _NET_BUFFER_SIZE)
            std::cout << "Invalid UDP message size : " << size << std::endl;
        this->_dataIn.push_back(this->_udpTmpBuffer);
    } else {
        std::cerr << "handleMsgUdp Error: " << error.message() << std::endl;
    }
    this->initServerNetwork();
}

void ServerNetwork::handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection)
{
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
    this->initServerNetwork();
}

void ServerNetwork::tcpMsgCli(_B_ASIO_TCP::endpoint endpoint, _STORAGE_DATA data)
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

void ServerNetwork::udpMsgCli(_B_ASIO_UDP::endpoint endpoint, _STORAGE_DATA data)
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

void ServerNetwork::tcpMsgAll(_STORAGE_DATA data)
{
    for (auto &connection : this->_listConnections) {
        connection->tcpMsg(data);
    }
}

void ServerNetwork::udpMsgAll(_STORAGE_DATA data)
{
    for (auto &connection : this->_listConnections) {
        connection->udpMsg(data);
    }
}

void ServerNetwork::closeConnection(_B_ASIO_TCP::endpoint endpoint)
{
    for (auto &connection : this->_listConnections) {
        if (connection->getTcpEndpoint() == endpoint) {
            connection->closeConnection();
            break;
        } else {
            std::cerr << "Client not found" << std::endl;
        }
    }
}

void ServerNetwork::updateConnection()
{
    for (auto &connection : this->_listConnections) {
        if (!connection->isConnected()) {
            if (connection->getThreadConnection().joinable())
                connection->getThreadConnection().join();
            this->_listConnections.erase(std::remove(this->_listConnections.begin(), this->_listConnections.end(), connection), this->_listConnections.end());
        }
    }
}

_QUEUE_TYPE &ServerNetwork::getQueueIn()
{
    return this->_dataIn;
}

_QUEUE_TYPE &ServerNetwork::getQueueOut()
{
    return this->_dataOut;
}

std::vector<boost::shared_ptr<Connection>> &ServerNetwork::getConnections()
{
    return this->_listConnections;
}
