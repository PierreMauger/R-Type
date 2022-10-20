#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "Connection.hpp"
#include "NetCommon.hpp"

namespace eng
{
    class Server
    {
        private:
            void handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection);
            void handleMsgUdp(const boost::system::error_code &error, size_t size);
            void initServer();

            boost::asio::io_context _ioContext;
            _B_ASIO_UDP::socket _udpSocket;
            _B_ASIO_TCP::acceptor _acceptor;
            std::vector<boost::shared_ptr<Connection>> _listConnections;
            _QUEUE_TYPE _dataIn;
            _QUEUE_TYPE _dataOut;
            std::thread _threadContext;
            _B_ASIO_UDP::endpoint _tmpEndpoint;
            _STORAGE_DATA _udpTmpBuffer;

        public:
            Server(uint16_t portUdp, uint16_t portTcp);
            ~Server();

            void run();
            void stop();

            void tcpMsgCli(_B_ASIO_TCP::endpoint endpoint, _STORAGE_DATA data);
            void udpMsgCli(_B_ASIO_UDP::endpoint endpoint, _STORAGE_DATA data);

            void tcpMsgAll(_STORAGE_DATA data);
            void udpMsgAll(_STORAGE_DATA data);

            void closeConnection(_B_ASIO_TCP::endpoint endpoint);
            void updateConnection();

            _QUEUE_TYPE &getQueueIn();
            _QUEUE_TYPE &getQueueOut();
            std::vector<boost::shared_ptr<Connection>> &getConnections();
    };
} // namespace eng

#endif /* !SERVER_HPP_ */