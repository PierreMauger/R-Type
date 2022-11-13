/**
 * @file EntityPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload an entity (parent class of the other preloads).
 * @copyright Epitech Rennes 2022
 */

#ifndef ENTITYPRELOAD_HPP
#define ENTITYPRELOAD_HPP

/// @cond
#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/Graphic/Graphic.hpp"
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
             * @brief Preloads the parallax.
             * @fn void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param graphic A reference to the engine graphics.
             * @param entityManager A reference to the EntityManager.
             * @param componentManager A reference to the ComponentManager.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
            {
                (void)graphic;
                (void)entityManager;
                (void)componentManager;
            }

            /**
             * @brief Creates a random value between a min and max.
             * @fn float createRandom(float min, float max)
             * @param min The min random value
             * @param max The max random value
             * @return The random float value
             */
            static float createRandom(float min, float max)
            {
                return (std::rand() % static_cast<int>(max - min + min));
            }
    };
}

#endif // ENTITYPRELOAD_HPP
