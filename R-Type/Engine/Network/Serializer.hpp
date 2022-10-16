#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Network/NetCommon.hpp"
#include "Includes.hpp"

#define MAGIC "R-TYPE/AMOGUS"
#define MAGIC_SIZE sizeof(MAGIC)

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

    class Serializer
    {
        private:
            template <typename T> std::size_t serializeComponent(_STORAGE_DATA &packet, std::size_t adv, T &component)
            {
                std::size_t i = 0;

                for (; i < sizeof(T); i++) {
                    packet[adv + i] = ((uint8_t *)&component)[i];
                }
                return adv + i;
            };

            template <typename T> std::size_t deserializeComponent(_STORAGE_DATA &packet, std::size_t adv, T &component)
            {
                std::size_t i = 0;

                for (; i < sizeof(T); i++) {
                    ((std::size_t *)&component)[i] = packet[adv + i];
                }
                return adv + i;
            };

            std::size_t insertMagic(_STORAGE_DATA &packet, std::size_t adv);
            bool checkMagic(_STORAGE_DATA &packet, std::size_t adv);

            std::size_t getEntityID(SyncID syncID, EntityManager &entityManager, ComponentManager &componentManager);

            std::size_t updateEntity(_STORAGE_DATA &packet, std::size_t id, std::size_t adv, ComponentManager &componentManager);

        public:
            Serializer();
            ~Serializer() = default;

            void handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                              std::shared_ptr<sf::Clock> clock);

            _STORAGE_DATA serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager);
            void synchronizeEntity(_STORAGE_DATA packet, EntityManager &entityManager, ComponentManager &componentManager);

            _STORAGE_DATA serializeInput(sf::Keyboard::Key input);
            void synchronizeInput(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                  std::shared_ptr<sf::Clock> clock);
    };
}

#endif // SERIALIZER_HPP
