/**
 * @file ScoreSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The score system
 * @copyright Epitech Rennes 2022
 */

#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

/// @cond
#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/System/ISystem.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The score system
     * @class ScoreSystem
     */
    class ScoreSystem : public virtual ISystem
    {
        private:
            std::size_t _textTag = (InfoComp::TEXT);
            std::size_t _controlTag = (InfoComp::CONTROLLABLE);

            bool findVessel(ComponentManager &componentManager, EntityManager &entityManager, Controllable &Controllable);

        public:
            /**
             * @brief ScoreSystem constructor
             * @fn ScoreSystem(Graphic &graphic, EntityManager &entityManager)
             * @param entityManager A reference to the EntityManager
             */
            ScoreSystem(EntityManager &entityManager);
            /**
             * @brief ScoreSystem destructor
             * @fn ~ScoreSystem()
             */
            ~ScoreSystem() = default;
            /**
             * @brief Update the ScoreSystem
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the ComponentManager
             * @param entityManager A reference to the EntityManager
             */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // SCORESYSTEM_HPP
