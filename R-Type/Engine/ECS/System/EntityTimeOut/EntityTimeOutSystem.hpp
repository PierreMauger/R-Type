/**
 * @file EntityTimeOutSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System of the inputs.
 * @copyright Epitech Rennes 2022
 */

#ifndef ENTITYTIMEOUTSYSTEM_HPP
#define ENTITYTIMEOUTSYSTEM_HPP

/// @cond
#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

/// @cond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief System of an input.
     * @class EntityTimeOutSystem
     */
    class EntityTimeOutSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Clock> _clock;

        public:
            /**
             * @brief EntityTimeOutSystem constructor.
             * @fn EntityTimeOutSystem(Graphic &graphic, EntityManager &entityManager)
             * @param graphic A reference to the Graphic
             * @param entityManager A reference to the EntityManager
             */
            EntityTimeOutSystem(Graphic &graphic, EntityManager &entityManager);
            /**
             * @brief EntityTimeOutSystem destructor.
             * @fn ~EntityTimeOutSystem
             */
            ~EntityTimeOutSystem() = default;
            /**
             * @brief Update the input system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
             */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // ENTITYTIMEOUTSYSTEM_HPP
