#include "Server/Server.hpp"

using namespace eng;

Server::Server(uint16_t portTcp) :
    _ioContext(),
    _acceptor(_ioContext, _B_ASIO_TCP::endpoint(_B_ASIO_TCP::v4(), portTcp))
{
    // if (portTcp)
        // throw std::runtime_error("Invalid port, must be different and between 0 and 65535");
    this->initServer();
}

Server::~Server()
{
    this->stop();
}

void Server::initServer()
{
    boost::shared_ptr<Connection> newConnection = boost::make_shared<Connection>(this->_ioContext, this->_dataIn);
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

void Server::handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection)
{
    if (!error) {
        newConnection->setTcpEndpoint(newConnection->getTcpSocket().remote_endpoint());
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "New TCP connection from " << newConnection->getTcpEndpoint().address().to_string() << std::endl;

        // Send the Udp IN port to the client
        std::cout << "Send the Udp IN port to the client" << std::endl;

        uint16_t portUdp = newConnection->getUdpSocketIn().local_endpoint().port();
        std::cout << "Udp IN port is " << portUdp << std::endl;
        newConnection->getTcpSocket().write_some(boost::asio::buffer(&portUdp, sizeof(portUdp)));

        // Get the Udp OUT port from the client
        std::cout << "Wait to get the Udp OUT port from the client.." << std::endl;
        newConnection->getTcpSocket().read_some(boost::asio::buffer(&portUdp, sizeof(portUdp)));
        std::cout << "Udp OUT port is " << portUdp << std::endl;

        // Set the Udp OUT port
        std::cout << "Set the Udp OUT port" << std::endl;
        newConnection->setUdpEndpoint(newConnection->getTcpEndpoint().address().to_string(), portUdp);

        // Run the new connection
        std::cout << "Run the new connection" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        newConnection->run();
        this->_listConnections.push_back(newConnection);
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
            if (connection->getThreadConnection().joinable())
                connection->getThreadConnection().join();
            this->_listConnections.erase(std::remove(this->_listConnections.begin(), this->_listConnections.end(), connection), this->_listConnections.end());
        }
    }
}

_QUEUE_TYPE &Server::getQueueIn()
{
    return this->_dataIn;
}

_QUEUE_TYPE &Server::getQueueOut()
{
    return this->_dataOut;
}

std::vector<boost::shared_ptr<Connection>> &Server::getConnections()
{
    return this->_listConnections;
}