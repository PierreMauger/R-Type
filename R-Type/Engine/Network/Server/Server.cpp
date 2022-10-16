#include "Server/Server.hpp"

using namespace eng;

Server::Server(uint16_t portUdp, uint16_t portTcp) :
    _ioContext(),
    _udpSocket(_ioContext, _B_ASIO_UDP::endpoint(_B_ASIO_UDP::v4(), portUdp)),
    _acceptor(_ioContext, _B_ASIO_TCP::endpoint(_B_ASIO_TCP::v4(), portTcp))
{
    if (portUdp == portTcp)
        throw std::runtime_error("Invalid port, must be different and between 0 and 65535");
    this->initServer();
}

Server::~Server()
{
    this->stop();
}

void Server::initServer()
{
    _STORAGE_DATA buffer;
    this->_udpSocket.async_receive_from(
        boost::asio::buffer(buffer),
        this->_tmpEndpoint,
        boost::bind(&Server::handleMsgUdp,
                    this,
                    boost::asio::placeholders::error,
                    buffer
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
    this->_threadContext = std::thread([this]() {
        this->_ioContext.run();
    });
    std::cout << "Server is running" << std::endl;
}

void Server::stop()
{
    // Stop all connections
    if (this->_udpSocket.is_open())
        this->_udpSocket.close();
    for (auto &connection : this->_listConnections) {
        if (connection->isConnected())
            connection->closeConnection();
        // if (connection->getThreadConnection().joinable())
            // connection->getThreadConnection().join();
    }
    this->_listConnections.clear();

    // Stop the ioContext
    if (!this->_ioContext.stopped())
        this->_ioContext.stop();
    if (this->_threadContext.joinable())
        this->_threadContext.join();
}

void Server::handleMsgUdp(const boost::system::error_code &error, _STORAGE_DATA buffer)
{
    if (!error) {
        std::cout << "New UDP message from " << this->_tmpEndpoint.address().to_string() << ":" << this->_tmpEndpoint.port() << std::endl;
        this->_dataIn.push_back(buffer);
    } else {
        std::cerr << "handleMsgUdp Error: " << error.message() << std::endl;
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
        newConnection->run();
        this->_listConnections.push_back(newConnection);
        // TODO send action structure or message for client connection in dataIn
        // this->_dataIn.push_back({'C'});
    } else {
        std::cerr << "handleNewTcp Error: " << error.message() << std::endl;
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

void Server::closeConnection(_B_ASIO_TCP::endpoint endpoint)
{
    for (auto &connection : this->_listConnections) {
        if (connection->getTcpEndpoint() == endpoint) {
            // TODO send action structure or message for client disconnection in dataIn
            // this->_dataIn.push_back({'D'});
            connection->closeConnection();
            break;
        } else {
            std::cerr << "Client not found" << std::endl;
        }
    }
}

void Server::updateConnection()
{
    for (auto &connection : this->_listConnections) {
        if (!connection->isConnected()) {
            // if (connection->getThreadConnection().joinable())
                // connection->getThreadConnection().join();
            // TODO send action structure or message for client disconnection in dataIn
            // this->_dataIn.push_back({'D'});
            this->_listConnections.erase(std::remove(this->_listConnections.begin(), this->_listConnections.end(), connection), this->_listConnections.end());
        }
    }
}

_QUEUE_TYPE &Server::getQueue()
{
    return this->_dataIn;
}