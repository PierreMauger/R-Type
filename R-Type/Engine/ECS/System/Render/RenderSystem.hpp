/**
 * @file RenderSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System of the render (graphics).
 * @copyright Epitech Rennes 2022
*/

#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

/// @cond
#include "Engine/ECS/System/GUI/GUISystem.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Loader/Loader.hpp"
#include "Includes.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief System of the render.
     * @class RenderSystem
    */
    class RenderSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<std::vector<sf::Sprite>> _sprites;
            void displayCooldownBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i);
            void displayLifeBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i);

        public:
<<<<<<< HEAD
            /**
             * @brief PhysicSystem constructor.
             * @fn PhysicSystem(std::shared_ptr<sf::RenderWindow> window)
             * @param window A shared pointer to the SFML render window.
             * @param clock A shared pointer to the clock of the game (for render timings and such).
             * @param loader A reference to the loader (with the images to render).
            */
            RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, Loader &loader);
            /**
             * @brief RenderSystem destructor.
             * @fn ~RenderSystem
            */
=======
            RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::Sprite>> sprites);
>>>>>>> 90197073cf3632fe21f6a30be244b2a96f037148
            ~RenderSystem() = default;
            /**
             * @brief Update the render system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
            */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // RENDERSYSTEM_HPP
