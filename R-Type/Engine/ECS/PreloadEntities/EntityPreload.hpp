/**
 * @file EntityPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload an entity (parent class of the other preloads).
 * @copyright Epitech Rennes 2022
 */

#ifndef ENTITYPRELOAD_HPP
#define ENTITYPRELOAD_HPP

/// @cond
#include <Includes.hpp>

#include "Engine/Engine.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief Preloads an entity.
     * @class EntityPreload
     */
    class EntityPreload
    {
        public:
            /**
             * @brief EntityPreload destructor.
             * @class ~EntityPreload
             */
            virtual ~EntityPreload() = default;

            /**
             * @brief Preloads an entity.
             * @fn virtual void preload(Engine &engine) = 0
             * @param engine A reference to the engine.
             */
            virtual void preload(Engine &engine) = 0;

            /**
             * @brief Creates a new entity.
             * @fn Entity &createEntity(Engine &engine)
             * @param engine A reference to the engine.
             * @return A reference to the new entity.
             */
            float createRandom(float min, float max)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(min, max);
                return dis(gen);
            }
    };
}

#endif // ENTITYPRELOAD_HPP
