/**
 * @file Client.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The client of the server.
 * @copyright Epitech Rennes 2022
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

/// @cond
#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Network/Connection.hpp"
#include "Includes.hpp"
#include "Room.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The server's client handling functions.
     * @class Client
     */
    class Client : public std::enable_shared_from_this<Client>
    {
        private:
            std::size_t _id;
            int _vesselId = -1;
            bool _isAlive = true;
            int _roomId = -1;
            bool _isReady = false;
            std::shared_ptr<Connection> _connection;

        public:
            /**
             * @brief Client constructor
             * @fn Client(std::shared_ptr<Connection> connection, std::size_t id)
             * @param connection A shared pointer to the connection between the server and the client.
             * @param id The id of the client
             */
            Client(std::shared_ptr<Connection> connection, std::size_t id);
            /**
             * @brief Client destructor
             * @fn ~Client()
             */
            ~Client() = default;

            /**
             * @brief Get the id of the vessel
             * @fn int getVesselId()
             * @return The id of the vessel
             */
            int getVesselId() const;
            /**
             * @brief Set the id of the vessel
             * @fn void setVesselId(int vesselId)
             * @param vesselId The id of the vessel
             */
            void setVesselId(int vesselId);

            /**
             * @brief Get if the client is alive
             * @fn bool isAlive()
             * @return The boolean representing if the client is alive
             */
            bool isAlive() const;
            /**
             * @brief Set if the client is alive
             * @fn void setAlive(bool isAlive)
             * @param isAlive The boolean representing if the client is alive or not
             */
            void setAlive(bool isAlive);

            /**
             * @brief Get the room id
             * @fn int getRoomId()
             * @return The room id
             */
            int getRoomId() const;
            /**
             * @brief Set the room id
             * @fn void setRoomId(int roomId)
             * @param roomId The room id
             */
            void setRoomId(int roomId);

            /**
             * @brief Get if the client is ready
             * @fn bool isReady()
             * @return The boolean representing if the client is ready
             */
            bool isReady() const;
            /**
             * @brief Set if the client is ready
             * @fn void setReady(bool isReady)
             * @param isReady The boolean representing if the client is ready or not
             */
            void setReady(bool isReady);

            /**
             * @brief Get the client connection
             * @fn std::shared_ptr<Connection> getConnection()
             * @return A shared pointer to the connection
             */
            std::shared_ptr<Connection> getConnection() const;

            /**
             * @brief Destroy the client
             * @fn void destroyClient(std::vector<Room> &rooms, EntityManager &entityManager, ComponentManager &componentManager)
             * @param rooms A shared pointer to the vector of rooms
             * @param entityManager A shared pointer to the EntityManager
             * @param componentManager A shared pointer to the ComponentManager
             */
            void destroyClient(std::vector<Room> &rooms, EntityManager &entityManager, ComponentManager &componentManager);

            /**
             * @brief Get the client id
             * @fn std::size_t getId()
             * @return The client id
             */
            std::size_t getId() const;

            /**
             * @brief Check if the client is the same as another client
             * @fn bool operator==(const Client &client)
             * @param client A shared pointer to the client to check
             * @return A boolean representing if the clients are the same or not
             */
            bool operator==(const Client &client) const;
    };
}

#endif // CLIENT_HPP
