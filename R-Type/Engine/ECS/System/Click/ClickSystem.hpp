#ifndef CLICKSYSTEM_HPP
#define CLICKSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"

namespace eng
{
    class ClickSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;

        public:
            ClickSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize);
            ~ClickSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // CLICKSYSTEM_HPP
