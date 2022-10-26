#ifndef GAMESERIALIZER_HPP
#define GAMESERIALIZER_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Network/NetCommon.hpp"
#include "Engine/Network/Room.hpp"
#include "Engine/Network/Serializer.hpp"
#include "Includes.hpp"

#define MAGIC "R-TYPE/AMOGUS"
#define MAGIC_SIZE sizeof(MAGIC)

namespace eng
{
    enum MenuPacketType {
        ROOM_EDIT,
        ROOM_ACTION,
        EVENT,

        UNKNOWN_MENU
    };

    enum RoomAction {
        JOIN,
        LEAVE,
        READY,
        UNREADY,
        START,

        UNKNOWN_ACTION
    };

    enum MenuEvent {
        GAME_START,
        GAME_END,

        UNKNOWN_EVENT
    };

    class MenuSerializer : private Serializer
    {
        private:
            Room getRoom(std::vector<Room> rooms, std::size_t id);

            void editRoom(CrudType crudType, std::vector<Room> &rooms, std::size_t id, std::size_t maxPlayers, std::size_t nbPlayers);

        public:
            MenuSerializer();
            ~MenuSerializer() = default;

            void handlePacket(_STORAGE_DATA packet);

            _STORAGE_DATA serializeRoomEdit(CrudType editType, Room &room);
            void deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms);

            _STORAGE_DATA serializeRoomAction(std::size_t id, RoomAction action);
            void deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms);

            _STORAGE_DATA serializeEvent(MenuEvent event);
            // void deserializeEvent(std::vector<uint8_t> packet);
    };
}

#endif // GAMESERIALIZER_HPP
