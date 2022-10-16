/**
 * @file SystemManager.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Manager of the systems.
 * @copyright Epitech Rennes 2022
 */

#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

/// @cond
#include "Engine/ECS/System/ISystem.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief Manager of the systems.
     * @class SystemManager
     */
    class SystemManager
    {
        private:
            std::vector<std::shared_ptr<ISystem>> _systems;

        public:
            /**
             * @brief Manager of the systems.
             * @class SystemManager
             */
            SystemManager();
            /**
             * @brief PhysicSystem destructor.
             * @fn ~SystemManager()
             */
            ~SystemManager();

            /**
             * @brief Add a system
             * @fn void addSystem(std::shared_ptr<ISystem> system)
             * @param system A shared pointer to the system to add.
             */
            void addSystem(std::shared_ptr<ISystem> system);
            /**
             * @brief Update the systems.
             * @fn void updateSystems(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
             */
            void updateSystems(ComponentManager &componentManager, EntityManager &entityManager);
            /**
             * @brief Get the vector of systems.
             * @fn std::vector<std::shared_ptr<ISystem>> &getSystems()
             * @return The vector of systems.
             */
            std::vector<std::shared_ptr<ISystem>> &getSystems();
    };
}

#endif // SYSTEMMANAGER_HPP
