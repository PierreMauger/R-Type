/**
 * @file SoundPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the vessel (player).
 * @copyright Epitech Rennes 2022
 */

#ifndef SOUNDPRELOAD_HPP
#define SOUNDPRELOAD_HPP

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
     * @brief Preloads the vessel.
     * @class SoundPreload
     */
    class SoundPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the vessel.
             * @fn SoundPreload
             * @param entityManager The entity manager.
             * @param componentManager The component manager.
             * @param syncId The sync id.
             * @param sound The sound.
             */
            static void preload(EntityManager &entityManager, ComponentManager &componentManager, std::shared_ptr<std::size_t> syncId, SoundID sound);
    };
}

#endif // SOUNDPRELOAD_HPP
