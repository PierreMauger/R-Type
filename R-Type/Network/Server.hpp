#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "NetCommon.hpp"
#include "Connection.hpp"

class Server {
    private:
        void handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection);
        void handleMsgUdp(const boost::system::error_code &error, _STORAGE_DATA buffer, size_t size, _B_ASIO_UDP::endpoint newEndpoint);
        void initServer();
        bool isConnected(boost::shared_ptr<Connection> client);

    protected:
        boost::asio::io_context _ioContext;
        _B_ASIO_UDP::socket _udpSocket;
        _B_ASIO_TCP::acceptor _acceptor;
        std::vector<boost::shared_ptr<Connection>> _listConnections;
        _QUEUE_TYPE _dataIn;
        std::thread _threadContext;

    public:
        Server(uint16_t portUdp, uint16_t portTcp);
        ~Server();
            
        void run();
        void stop();

        void tcpMsgCli(_B_ASIO_TCP::endpoint endpoint, _STORAGE_DATA data);
        void udpMsgCli(_B_ASIO_UDP::endpoint endpoint, _STORAGE_DATA data);

        void tcpMsgAll(_STORAGE_DATA data);
        void udpMsgAll(_STORAGE_DATA data);

        virtual void newConnect(_B_ASIO_TCP::endpoint endpoint);

        virtual void updateAction();
};

#endif /* !SERVER_HPP_ */