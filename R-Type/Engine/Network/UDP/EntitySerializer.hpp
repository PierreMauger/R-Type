#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Network/UDP/Protocol.hpp"
#include "Includes.hpp"

namespace eng
{
    class EntitySerializer
    {
        private:
            template <typename T> void serializeComponent(std::vector<uint8_t> &packet, T &component)
            {
                for (uint8_t i = 0; i < sizeof(T); i++) {
                    packet.push_back(((uint8_t *)&component)[i]);
                }
            };

            template <typename T> std::size_t deserializeComponent(std::vector<uint8_t> &packet, std::size_t adv, T &component)
            {
                std::size_t i = 0;

                for (; i < sizeof(T); i++) {
                    ((std::size_t *)&component)[i] = packet[adv + i];
                }
                return (adv + i);
            };

            void insertMagic(std::vector<uint8_t> &packet);
            std::size_t getEntityID(SyncID syncID, EntityManager &entityManager, ComponentManager &componentManager);

            std::size_t updateEntity(std::vector<uint8_t> &packet, std::size_t id, std::size_t &adv, ComponentManager &componentManager);

        public:
            EntitySerializer();
            ~EntitySerializer() = default;

            std::vector<uint8_t> serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager);
            void synchronizeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // SERIALIZER_HPP
