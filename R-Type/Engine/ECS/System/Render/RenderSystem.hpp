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
#include "Engine/Graphic/Graphic.hpp"
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
            std::shared_ptr<sf::Vector2f> _screenSize;
            sf::Text _text;
            sf::Font _font;

            std::size_t _renderTag = (InfoComp::POS | InfoComp::SPRITEID);
            std::size_t _textTag = (InfoComp::TEXT);

            bool displayCooldownBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i);
            bool displayLifeBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i);

        public:
            /**
             * @brief RenderSystem constructor.
             * @fn RenderSystem(Graphic &graphic, EntityManager &entityManager)
             * @param graphic A reference to the Graphic
             * @param entityManager A reference to the EntityManager
             * @param sprites A shared pointer to the vector of sprites to render
             */
            RenderSystem(Graphic &graphic, EntityManager &entityManager, std::shared_ptr<std::vector<sf::Sprite>> sprites);
            /**
             * @brief RenderSystem destructor.
             * @fn ~RenderSystem
             */
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
