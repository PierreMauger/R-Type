#ifndef SERVERNETWORK_HPP_
#define SERVERNETWORK_HPP_

#include "Connection.hpp"

namespace eng
{
    class ServerNetwork
    {
        private:
            void handleTimeout(const boost::system::error_code &error);
            void handleNewTcp(const boost::system::error_code &error, boost::shared_ptr<Connection> newConnection);
            void initServerNetwork();

            boost::asio::io_context _ioContext;
            boost::asio::deadline_timer _timer;
            _B_ASIO_TCP::acceptor _acceptor;
            std::vector<boost::shared_ptr<Connection>> _listConnections;
            _QUEUE_TYPE _dataIn;
            _QUEUE_TYPE _dataOut;
            std::thread _threadContext;

        public:
            ServerNetwork(uint16_t portTcp);
            ~ServerNetwork();

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

#endif /* !SERVERNETWORK_HPP_ */
