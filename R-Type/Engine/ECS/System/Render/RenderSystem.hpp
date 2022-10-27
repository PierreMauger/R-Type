#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "Engine/ECS/System/GUI/GUISystem.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Loader/Loader.hpp"
#include "Includes.hpp"

namespace eng
{
    class RenderSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<std::vector<sf::Sprite>> _sprites;
            std::shared_ptr<sf::Vector2f> _screenSize;
            sf::Text _text;
            sf::Font _font;
            void displayCooldownBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i);
            void displayLifeBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i);

        public:
            RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::Sprite>> sprites,
                         std::shared_ptr<sf::Vector2f>);
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // RENDERSYSTEM_HPP
