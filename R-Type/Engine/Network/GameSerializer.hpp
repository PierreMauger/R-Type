#ifndef GAMESERIALIZER_HPP
#define GAMESERIALIZER_HPP

#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Network/NetCommon.hpp"
#include "Engine/Network/Serializer.hpp"
#include "Includes.hpp"

namespace eng
{
    enum GamePacketType {
        ENTITY,
        INPUT,

        UNKNOWN_GAME
    };

    class GameSerializer : private Serializer
    {
        private:
            template <typename T> void serializeComponent(std::vector<uint8_t> &packet, T *component)
            {
                for (uint8_t i = 0; i < sizeof(T); i++) {
                    packet.push_back(((uint8_t *)component)[i]);
                }
            };

            template <typename T> void deserializeComponent(std::vector<uint8_t> &packet, std::size_t &adv, T *component)
            {
                std::size_t i = 0;

                for (; i < sizeof(T); i++) {
                    ((uint8_t *)component)[i] = packet.at(adv + i);
                }
                adv += i;
            };

            template <typename T> void updateEntity(std::vector<uint8_t> &packet, std::size_t id, std::size_t &adv, ComponentManager &componentManager)
            {
                T component = T();

                deserializeComponent(packet, adv, &component);
                componentManager.getSingleComponent<T>(id) = component;
            };

            std::size_t getEntityID(SyncID syncID, EntityManager &entityManager, ComponentManager &componentManager);

            void pushComponents(std::vector<uint8_t> &packet, std::size_t mask, std::size_t id, ComponentManager &componentManager);
            void getComponents(std::vector<uint8_t> &packet, std::size_t id, std::size_t mask, std::size_t &adv, ComponentManager &componentManager);

        public:
            GameSerializer();
            ~GameSerializer() = default;

            void handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                              std::shared_ptr<sf::Clock> clock);

            _STORAGE_DATA serializeEntity(std::size_t id, CrudType type, EntityManager &entityManager, ComponentManager &componentManager);
            void deserializeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager);

            _STORAGE_DATA serializeInput(sf::Keyboard::Key input);
            void deserializeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                  std::shared_ptr<sf::Clock> clock);
    };
}

#endif // GAMESERIALIZER_HPP
