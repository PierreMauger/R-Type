#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Includes.hpp"

namespace eng
{
    enum PacketType {
        ENTITY,
        EVENT,
        INPUT
    };

    class EntitySerializer

    {
        public:
            EntitySerializer();
            ~EntitySerializer() = default;

            std::vector<uint8_t> serializeEntity(std::size_t id, EntityManager &entityManager, ComponentManager &componentManager);
            void synchronizeEntity(std::vector<uint8_t> entity, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // SERIALIZER_HPP
