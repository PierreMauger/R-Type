#pragma once

#include "common.hpp"
#include "message.hpp"
#include "queue.hpp"

namespace net
{
    template <typename T> class connection : public std::enable_shared_from_this<connection<T>>
    {
        protected:
            queue<message<T>> _queueMessagesOut;
            queue<owned_message<T>> &_queueMessagesIn;
            asio::ip::tcp::socket _socket;
            asio::ip::udp::socket _udpSocket;
            asio::io_context &_asioContext;

        public:
            connection();
            virtual ~connection();
            bool Connect();
            bool Disconnect();
            bool IsConnected();
            bool Send(message<T> &msg);
    };
} // namespace net