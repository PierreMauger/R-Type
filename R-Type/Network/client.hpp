#pragma once

#include "common.hpp"
#include "connection.hpp"
#include "message.hpp"
#include "queue.hpp"

namespace net
{
    template <typename T> class client
    {
        private:
            queue<owned_message<T>> _queueMessagesIn;

        protected:
            asio::io_context _asioContext;
            std::thread _threadContext;
            asio::ip::tcp::socket _tcpSocket;
            asio::ip::udp::socket _udpSocket;
            std::unique_ptr<connection<T>> _connection;

        public:
            client();
            virtual ~client();
            bool Connect(const std::string &host, const uint16_t port);
            void Disconnect();
            bool IsConnected();
            queue<owned_message<T>> &GetQueueIn();
    };
} // namespace net