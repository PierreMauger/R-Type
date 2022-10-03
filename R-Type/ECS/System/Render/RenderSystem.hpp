#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "ECS/System/ISystem.hpp"
#include "ECS/System/Render/GUI.hpp"
#include "Includes.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace ECS
{
    class RenderSystem : public virtual ISystem
    {
        private:
            std::size_t id;
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Clock> _clock;
            std::map<std::size_t, std::pair<sf::RectangleShape, sf::RectangleShape>> _cooldownBar;
            std::array<sf::Texture, 10> _texture; // array car sf::vector stock dans la mémoire de manière bizarre donc white square problem sfml
            std::vector<sf::Sprite> _sprites;
            std::map<std::size_t, sf::Color> _color;
            GUI _gui;
            void displayCooldownBar(std::size_t i, ComponentManager &componentManager);

        public:
            RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock);
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // RENDERSYSTEM_HPP
