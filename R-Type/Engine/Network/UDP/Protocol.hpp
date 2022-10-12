#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Includes.hpp"

#define FOOTER "\n"

namespace eng
{
    enum PacketType {
        ENTITY,
        INPUT
    };

    enum EntityType {
        CREATE,
        DESTROY,
        UPDATE
    };
}

#endif // PROTOCOL_HPP
