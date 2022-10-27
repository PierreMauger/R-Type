#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Engine/Network/Connection.hpp"
#include "Includes.hpp"

namespace eng
{
    class Client
    {
        private:
            std::size_t _vesselId;
            bool _isAlive;
            std::size_t _roomId;
            bool _isReady;
            std::shared_ptr<Connection> _connection;

        public:
            Client(std::shared_ptr<Connection> connection);
            ~Client() = default;
    };
}

#endif // CLIENT_HPP
