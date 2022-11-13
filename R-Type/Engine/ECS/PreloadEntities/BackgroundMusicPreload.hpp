/**
 * @file BackgroundMusicPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The background music preloader
 * @copyright Epitech Rennes 2022
 */

#ifndef BACKGROUNDMUSICPRELOAD_HPP
#define BACKGROUNDMUSICPRELOAD_HPP

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
     * @brief The background music preloader
     * @class BackgroundMusicPreload
     */
    class BackgroundMusicPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the background music.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param graphic A reference to the engine graphics.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
            /**
             * @brief Preloads the music.
             * @fn void preloadMusic(EntityManager &entityManager, ComponentManager &componentManager, std::size_t id)
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             * @param id The music id.
             */
            static void preloadMusic(EntityManager &entityManager, ComponentManager &componentManager, std::size_t id);
    };
}

#endif // BACKGROUNDMUSICPRELOAD_HPP
