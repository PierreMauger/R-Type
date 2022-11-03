#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Engine/Network/Connection.hpp"
#include "Includes.hpp"

namespace eng
{
    class Client : public std::enable_shared_from_this<Client>
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

            std::size_t getVesselId() const;
            void setVesselId(std::size_t vesselId);

            bool isAlive() const;
            void setAlive(bool isAlive);

            std::size_t getRoomId() const;
            void setRoomId(std::size_t roomId);

            bool isReady() const;
            void setReady(bool isReady);

            std::shared_ptr<Connection> getConnection() const;
    };
}

#endif // CLIENT_HPP
