/**
 * @file Engine.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The engine of the game containing the ECS, the graphics and the loader.
 * @copyright Epitech Rennes 2022
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP

/// @cond
#include "Engine/ECS/ECS.hpp"
#include "Engine/Graphic/Graphic.hpp"
#include "Engine/Loader/Loader.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    class ECS;

    /**
     * @brief The engine of the game containing the ECS, the graphics and the loader.
     * @class Engine
     */
    class Engine
    {
        private:
            Loader _loader;
            ECS _ecs;
            Graphic _graphic;

            void updateSize(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size);
            void updateSpeed(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size);
            void updatePos(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size);
            void updateParallax(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size);
            void updateAppDis(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, sf::Vector2f lastSize, sf::Vector2f size);

        public:
            /**
             * @brief Engine constructor.
             * @fn Engine()
             */
            Engine();
            /**
             * @brief Engine destructor.
             * @fn ~Engine()
             */
            ~Engine() = default;

            /**
             * @brief Get a reference to the engine's ECS.
             * @fn ECS &getECS()
             * @return A reference to the ECS
             */
            ECS &getECS();
            /**
             * @brief Get a reference to the engine's graphics.
             * @fn Graphic &getGraphic()
             * @return A reference to the Graphic
             */
            Graphic &getGraphic();
            /**
             * @brief Get a reference to the engine's loader.
             * @fn Loader &getLoader()
             * @return A reference to the Loader
             */
            Loader &getLoader();
            /**
             * @brief Update the size of the window
             * @fn void updateSizeWindow()
             */
            void updateSizeWindow(sf::Vector2f lastSize);
            void updateSizeWindowId(sf::Vector2f lastSize, std::size_t i);
    };
}

#endif // ENGINE_HPP
