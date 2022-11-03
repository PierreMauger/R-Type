/**
 * @file MenuSerializer.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The menu serializer
 * @copyright Epitech Rennes 2022
 */

#ifndef GAMESERIALIZER_HPP
#define GAMESERIALIZER_HPP

/// @cond
#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Network/NetCommon.hpp"
#include "Engine/Network/Room.hpp"
#include "Engine/Network/Serializer.hpp"
#include "Includes.hpp"
/// @endcond

#define MAGIC "R-TYPE/AMOGUS"
#define MAGIC_SIZE sizeof(MAGIC)

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The menu packet type enum
     * @enum MenuPacketType
     */
    enum MenuPacketType {
        ROOM_EDIT,
        ROOM_ACTION,
        EVENT,

        UNKNOWN_MENU
    };

    /**
     * @brief The room action enum
     * @enum RoomAction
     */
    enum RoomAction {
        JOIN,
        LEAVE,
        READY,
        UNREADY,

        UNKNOWN_ACTION
    };

    /**
     * @brief The menu event enum
     * @enum MenuEvent
     */
    enum MenuEvent {
        GAME_START,
        GAME_END,

        UNKNOWN_EVENT
    };

    /**
     * @brief The menu serializer
     * @class MenuSerializer
     */
    class MenuSerializer : protected Serializer
    {
        protected:
            std::vector<Room>::iterator getRoom(std::vector<Room> rooms, std::size_t id);

            void editRoom(CrudType crudType, std::vector<Room> &rooms, std::size_t id, std::size_t maxPlayers, std::size_t nbPlayers);

        public:
            /**
             * @brief MenuSerializer constructor.
             * @fn MenuSerializer()
             */
            MenuSerializer();
            /**
             * @brief MenuSerializer destructor.
             * @fn ~MenuSerializer()
             */
            ~MenuSerializer() = default;

            /**
             * @brief Handle a menu packet.
             * @fn handlePacket(_STORAGE_DATA packet)
             * @param packet The packet to handle.
             */
            void handlePacket(_STORAGE_DATA packet, std::vector<Room> &rooms);

            /**
             * @brief Serialize a room edit
             * @fn _STORAGE_DATA serializeRoomEdit(CrudType editType, Room &room)
             * @param type The type of operation to perform on the entity
             * @param room A reference to the room
             * @return The serialized packet
             */
            _STORAGE_DATA serializeRoomEdit(CrudType editType, Room &room);
            /**
             * @brief Deserialize a room edit
             * @fn void deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms)
             * @param packet The serialized packet
             * @param rooms A reference to the vector of rooms
             */
            void deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms);

            /**
             * @brief Serialize a room action
             * @fn _STORAGE_DATA serializeRoomAction(std::size_t id, RoomAction action)
             * @param id The id of the packet
             * @param action A room action
             * @return The serialized packet
             */
            _STORAGE_DATA serializeRoomAction(std::size_t id, RoomAction action);
            /**
             * @brief Deserialize a room action
             * @fn void deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms)
             * @param packet The serialized packet
             * @param rooms A reference to the vector of rooms
             */
            void deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms);

            /**
             * @brief Serialize an event
             * @fn _STORAGE_DATA serializeEvent(MenuEvent event)
             * @param event Event to serialize
             * @return The serialized packet
             */
            _STORAGE_DATA serializeEvent(MenuEvent event);

            /**
             * @brief Serialize an event
             * @fn void deserializeEvent()
             * @param event Event to deserialize
             */
            void deserializeEvent();
    };
}

#endif // GAMESERIALIZER_HPP
