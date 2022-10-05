#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "Engine/ECS/System/GUI/GUISystem.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Loader/Loader.hpp"
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

            std::shared_ptr<std::vector<sf::Sprite>> _sprites;

        public:
            RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, Loader &loader);
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // RENDERSYSTEM_HPP
