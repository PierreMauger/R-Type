/**
 * @file LobbyPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the lobby.
 * @copyright Epitech Rennes 2022
 */

#ifndef LOBBYPRELOAD_HPP
#define LOBBYPRELOAD_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief Preloads the lobby.
     * @class LobbyPreload
     */
    class LobbyPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the lobby.
             * @fn static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // LOBBYPRELOAD_HPP
