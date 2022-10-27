#ifndef GAMESERIALIZER_HPP
#define GAMESERIALIZER_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Network/NetCommon.hpp"
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
        public:
            MenuSerializer();
            ~MenuSerializer() = default;

            void handlePacket(_STORAGE_DATA packet); // TODO vector of rooms

            // _STORAGE_DATA serializeRoomEdit(std::string name, std::size_t maxPlayers, std::size_t nbPlayers, bool isReady);
    };
}

#endif // GAMESERIALIZER_HPP
