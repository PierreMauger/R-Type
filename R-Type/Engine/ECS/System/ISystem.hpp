/**
 * @file ISystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Interface of the system.
 * @copyright Epitech Rennes 2022
 */

#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

/// @cond
#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief Interface of the system.
     * @class ISystem
     */
    class ISystem
    {
        public:
            /**
             * @brief PhysicSystem destructor.
             * @fn ~ISystem()
             */
            virtual ~ISystem() = default;
            /**
             * @brief Abstract update function.
             * @fn virtual void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
             */
            virtual void update(ComponentManager &componentManager, EntityManager &entityManager) = 0;
    };
}

#endif // ISYSTEM_HPP
