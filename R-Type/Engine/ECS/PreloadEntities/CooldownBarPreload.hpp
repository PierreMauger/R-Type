/**
 * @file CooldownBarPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the cooldown bar.
 * @copyright Epitech Rennes 2022
 */

#ifndef COOLDOWNBARPRELOAD_HPP
#define COOLDOWNBARPRELOAD_HPP

/// @cond
#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief Preloads the cooldown bar.
     * @class CooldownBarPreload
     */
    class CooldownBarPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the cooldown bar.
             * @fn void preload(Engine &engine) override
             * @param engine A reference to the engine.
             */
            void preload(Engine &engine) override;
    };
}

#endif // COOLDOWNBARPRELOAD_HPP
