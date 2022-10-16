/**
 * @file ECS.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The Engine's ECS (Entity Component System, see the readme for more infos).
 * @copyright Epitech Rennes 2022
*/

#ifndef ECS_HPP
#define ECS_HPP

/// @cond
#include "Engine/ECS/Component/ComponentManager.hpp"
#include "Engine/ECS/Entity/EntityManager.hpp"
#include "Engine/ECS/System/Animation/AnimationSystem.hpp"
#include "Engine/ECS/System/Enemy/EnemySystem.hpp"
#include "Engine/ECS/System/GUI/GUISystem.hpp"
#include "Engine/ECS/System/Input/InputSystem.hpp"
#include "Engine/ECS/System/Physic/PhysicSystem.hpp"
#include "Engine/ECS/System/Render/RenderSystem.hpp"
#include "Engine/ECS/System/Score/ScoreSystem.hpp"
#include "Engine/ECS/System/Sound/SoundSystem.hpp"
#include "Engine/ECS/System/SystemManager.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief The Engine's ECS (Entity Component System, see the readme for more infos).
     * @class ECS
    */
    class ECS
    {
        private:
            EntityManager _entityManager;
            ComponentManager _componentManager;
            SystemManager _systemManager;

        public:
            /**
             * @brief ECS constructor.
             * @fn ECS()
            */
            ECS();
            /**
             * @brief ECS destructor.
             * @fn ~ECS()
            */
            ~ECS() = default;

            /**
             * @brief Get a reference to the ECS' EntityManager.
             * @fn EntityManager &getEntityManager()
             * @return The EntityManager
            */
            EntityManager &getEntityManager();
            /**
             * @brief Get a reference to the ECS' ComponentManager.
             * @fn ComponentManager &getComponentManager()
             * @return The ComponentManager
            */
            ComponentManager &getComponentManager();
            /**
             * @brief Get a reference to the ECS' SystemManager.
             * @fn SystemManager &getSystemManager()
             * @return The SystemManager
            */
            SystemManager &getSystemManager();

            /**
             * @brief Update the ECS.
             * @fn void update()
            */
            void update();
    };
}

#endif // ECS_HPP
