#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Network/Connection.hpp"
#include "Includes.hpp"
#include "Room.hpp"

namespace eng
{
    class Client : public std::enable_shared_from_this<Client>
    {
        private:
            int _vesselId = -1;
            bool _isAlive = -1;
            int _roomId = -1;
            bool _isReady = false;
            std::shared_ptr<Connection> _connection;

        public:
            Client(std::shared_ptr<Connection> connection);
            ~Client() = default;

            int getVesselId() const;
            void setVesselId(int vesselId);

            bool isAlive() const;
            void setAlive(bool isAlive);

            int getRoomId() const;
            void setRoomId(int roomId);

            bool isReady() const;
            void setReady(bool isReady);

            std::shared_ptr<Connection> getConnection() const;

            void destroyClient(std::vector<Room> &rooms, EntityManager &entityManager, ComponentManager &componentManager);

            bool operator==(const Client &client) const;
    };
}

#endif // CLIENT_HPP
