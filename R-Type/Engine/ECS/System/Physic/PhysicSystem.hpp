/**
 * @file PhysicSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System of the physics.
 * @copyright Epitech Rennes 2022
*/

#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Graphic/Graphic.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief System of the physics.
     * @class PhysicSystem
    */
    class PhysicSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;
            sf::Rect<float> _rect1;
            sf::Rect<float> _rect2;
            void createBonus(std::size_t id, std::size_t drop, ComponentManager &componentManager, EntityManager &entityManager);
            bool checkAppareance(ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel);
            bool checkDisappearance(EntityManager &entityManager, ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel);
            bool checkColision(Position &pos, Position &pos2, Size &sz, Size &sz2);
            bool collisionBonus(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos);
            bool collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos);
            bool collisionFireball(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos);

        public:
            /**
             * @brief PhysicSystem constructor.
             * @fn PhysicSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize)
             * @param window A shared pointer to the SFML render window.
             * @param screenSize A shared pointer to the screen size
            */
            PhysicSystem(Graphic &graphic);
            /**
             * @brief PhysicSystem destructor.
             * @fn ~PhysicSystem
            */
            ~PhysicSystem() = default;
            /**
             * @brief Update the physics system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
            */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // PHYSICSYSTEM_HPP
