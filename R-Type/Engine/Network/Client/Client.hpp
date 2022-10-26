#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "Connection.hpp"
#include "NetCommon.hpp"

namespace eng
{
    class Client
    {
        private:
            void initClient();
            void open();

            boost::asio::io_context _ioContext;
            _B_ASIO_TCP::resolver _resolver;
            boost::shared_ptr<Connection> _connection;
            _QUEUE_TYPE _dataIn;
            std::thread _threadContext;

        public:
            Client(std::string ip, uint16_t portTcp);
            ~Client();

            void run();
            void stop();
            bool isConnected();

            void tcpMsg(_STORAGE_DATA data);
            void udpMsg(_STORAGE_DATA data);

            _QUEUE_TYPE &getQueueIn();
            _QUEUE_TYPE &getQueueOut();
    };
} // namespace eng

#endif /* !CLIENT_HPP_ */