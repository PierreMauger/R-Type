/**
 * @file ServerMenuSerializer.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The menu serializer
 * @copyright Epitech Rennes 2022
 */

#ifndef SERVERMENUSERIALIZER_HPP
#define SERVERMENUSERIALIZER_HPP

/// @cond
#include "Client.hpp"
#include "Engine/Network/MenuSerializer.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The menu serializer
     * @class ServerMenuSerializer
     */
    class ServerMenuSerializer : public MenuSerializer
    {
        public:
            /**
             * @brief ServerMenuSerializer constructor.
             * @fn ServerMenuSerializer()
             */
            ServerMenuSerializer();
            /**
             * @brief ServerMenuSerializer destructor.
             * @fn ~ServerMenuSerializer()
             */
            ~ServerMenuSerializer() = default;

            /**
             * @brief Handle a menu packet.
             * @fn handlePacket(_STORAGE_DATA packet)
             * @param packet The packet to handle.
             */
            void handlePacket(_STORAGE_DATA packet, std::vector<Room> &rooms, Client &client, std::size_t &roomCount);

            /**
             * @brief Deserialize a room action
             * @fn void deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms)
             * @param packet The serialized packet
             * @param rooms A reference to the vector of rooms
             */
            void deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms, Client &client);

            /**
             * @brief Deserialize a room edit
             * @fn void deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms)
             * @param packet The serialized packet
             * @param rooms A reference to the vector of rooms
             */
            void deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms, std::size_t &roomCount);

            /**
             * @brief Serialize an event
             * @fn void deserializeEvent()
             * @param event Event to deserialize
             */
            void deserializeEvent();
    };
}

#endif // SERVERMENUSERIALIZER_HPP
