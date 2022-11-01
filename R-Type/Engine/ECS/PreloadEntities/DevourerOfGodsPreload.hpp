/**
 * @file DevourerOfGodsPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the Devourer Of Gods (terraria boss).
 * @copyright Epitech Rennes 2022
 */

#ifndef DEVOUREROFGODSPRELOAD_HPP
#define DEVOUREROFGODSPRELOAD_HPP

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
     * @brief Preloads the Devourer Of Gods.
     * @class DevourerOfGodsPreload
     */
    class DevourerPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the Devourer Of Gods.
             * @fn void preload(Engine &engine) override
             * @param engine A reference to the engine.
             */
            void preload(Engine &engine) override;
            static void preload(Engine &engine, float x, float y);
    };
}

#endif // DEVOUREROFGODSPRELOAD_HPP
