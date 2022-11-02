/**
 * @file ScoreTextPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the score text.
 * @copyright Epitech Rennes 2022
*/

#ifndef SCORETEXTPRELOAD_HPP
#define SCORETEXTPRELOAD_HPP

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
     * @brief Preloads the score text.
     * @class ScoreTextPreload
    */
    class ScoreTextPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the score text.
             * @fn static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param engine A reference to the engine.
            */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // SCORETEXTPRELOAD_HPP
