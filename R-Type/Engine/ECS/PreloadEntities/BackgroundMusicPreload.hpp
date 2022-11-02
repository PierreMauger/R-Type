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
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager) override
             * @param engine A reference to the engine.
            */
            void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager) override;
    };
}

#endif // BACKGROUNDMUSICPRELOAD_HPP
