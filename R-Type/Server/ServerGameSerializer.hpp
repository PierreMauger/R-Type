/**
 * @file ServerGameSerializer.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The game serializer
 * @copyright Epitech Rennes 2022
 */

#ifndef SERVERGAMESERIALIZER_HPP
#define SERVERGAMESERIALIZER_HPP

/// @cond
#include "Client.hpp"
#include "Engine/Network/GameSerializer.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The game serializer
     * @enum ServerGameSerializer
     */
    class ServerGameSerializer : public GameSerializer
    {
        public:
            /**
             * @brief ServerGameSerializer constructor.
             * @fn ServerGameSerializer()
             */
            ServerGameSerializer();
            /**
             * @brief ServerGameSerializer destructor.
             * @fn ~ServerGameSerializer()
             */
            ~ServerGameSerializer() = default;

            /**
             * @brief Handle a game packet.
             * @fn handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Client &client)
             * @param packet The packet to handle.
             * @param id The id of the packet.
             * @param entityManager A reference to the EntityManager
             * @param componentManager A reference to the ComponentManager
             * @param client A reference to the Client who send the packet
             */
            void handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Client &client);

            /**
             * @brief Deserialize an input
             * @fn void deserializeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager)
             * @param packet The serialized packet
             * @param id The id of the packet
             * @param entityManager A reference to the EntityManager
             * @param componentManager A reference to the ComponentManager
             * @param client A reference to the Client who send the packet
             */
            void deserializeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Client &client);
    };
}

#endif // SERVERGAMESERIALIZER_HPP
