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

    class MenuSerializer : private Serializer
    {
        private:
        public:
            MenuSerializer();
            ~MenuSerializer() = default;
    };
}

#endif // GAMESERIALIZER_HPP
