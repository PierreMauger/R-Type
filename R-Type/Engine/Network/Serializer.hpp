/**
 * @file Serializer.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The network serializer (formats packets to be sent through network).
 * @copyright Epitech Rennes 2022
*/

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

/// @cond
#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Input/Input.hpp"
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
     * @brief The type of the packet to be sent.
     * @enum PacketType
    */
    enum PacketType {
        ENTITY,
        INPUT
    };

    /**
     * @brief The type of the entity packet to be sent.
     * @enum EntityType
    */
    enum EntityType {
        CREATE,
        DESTROY,
        UPDATE
    };
    /**
     * @brief The network serializer (formats packets to be sent through network).
     * @class Serializer
    */
    class Serializer
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
            bool checkMagic(std::vector<uint8_t> &packet, std::size_t adv);

            std::size_t getEntityID(SyncID syncID, EntityManager &entityManager, ComponentManager &componentManager);
            std::size_t updateEntity(std::vector<uint8_t> &packet, std::size_t id, std::size_t &adv, ComponentManager &componentManager);

        public:
            /**
             * @brief Serializer constructor.
             * @fn Serializer()
            */
            Serializer();
            /**
             * @brief Serializer destructor.
             * @fn ~Serializer()
            */
            ~Serializer() = default;

            /**
             * @brief Handle a packet.
             * @fn void handlePacket(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input, std::shared_ptr<sf::Clock> clock)
             * @param packet The packet (represented as a vector of ints) to handle.
             * @param id The index of the entity in the packet.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param input A reference to the input in the packet.
             * @param clock A shared pointer to the clock in the packet.
            */
            void handlePacket(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                              std::shared_ptr<sf::Clock> clock);

            /**
             * @brief Serialize an entity.
             * @fn std::vector<uint8_t> serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager)
             * @param id The index of the entity to serialize in the packet.
             * @param type The type of the entity to serialize.
             * @param componentManager A reference to the ComponentManager.
             * @return The packet containing the entity.
            */
            std::vector<uint8_t> serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager);
            /**
             * @brief Synchronize an entity
             * @fn void synchronizeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager)
             * @param packet The packet (represented as a vector of ints) containing the entity to serialize.
             * @param type The type of the entity.
             * @param componentManager A reference to the ComponentManager.
            */
            void synchronizeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager);

            /**
             * @brief Serialize an input.
             * @fn std::vector<uint8_t> serializeInput(sf::Keyboard::Key input)
             * @param input The input to serialize.
             * @return The packet containing the input.
            */
            std::vector<uint8_t> serializeInput(sf::Keyboard::Key input);
            /**
             * @brief Synchronize an input
             * @fn void synchronizeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input, std::shared_ptr<sf::Clock> clock)
             * @param packet The packet (represented as a vector of ints) to synchronize.
             * @param id The index of the index in the packet.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param input A reference to the input in the packet.
             * @param clock A shared pointer to the clock in the packet.
            */
            void synchronizeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                  std::shared_ptr<sf::Clock> clock);
    };
}

#endif // SERIALIZER_HPP
