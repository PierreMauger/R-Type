#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"
#include "Includes.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace eng
{
    class RenderSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Clock> _clock;
            std::array<sf::Texture, 10> _texture; // array car sf::vector stock dans la mémoire de manière bizarre donc white square problem sfml
            std::vector<sf::Sprite> _sprites;

        public:
            RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock);
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // RENDERSYSTEM_HPP
