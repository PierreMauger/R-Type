#ifndef CLIENTNETWORK_HPP_
#define CLIENTNETWORK_HPP_

#include "Connection.hpp"

namespace eng
{
    class ClientNetwork
    {
        private:
            void handleMsgUdp(const boost::system::error_code &error, size_t size);
            void initClientNetwork();
            void open();

            boost::asio::io_context _ioContext;
            _B_ASIO_TCP::resolver _resolver;
            _B_ASIO_UDP::socket _udpSocket;
            boost::shared_ptr<Connection> _connection;
            _QUEUE_TYPE _dataIn;
            _QUEUE_TYPE _dataOut;
            std::thread _threadContext;
            _B_ASIO_UDP::endpoint _tmpEndpoint;
            _STORAGE_DATA _udpTmpBuffer;

        public:
            ClientNetwork(std::string ip, uint16_t portUdp, uint16_t portTcp);
            ~ClientNetwork();

            void run();
            void stop();
            bool isConnected();

            void tcpMsg(_STORAGE_DATA data);
            void udpMsg(_STORAGE_DATA data);

            _QUEUE_TYPE &getQueueIn();
            _QUEUE_TYPE &getQueueOut();
    };
} // namespace eng

#endif /* !CLIENTNETWORK_HPP_ */
