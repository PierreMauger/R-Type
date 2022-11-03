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
             * @fn static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // BACKGROUNDMUSICPRELOAD_HPP
