#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"

namespace eng
{
    class InputSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Event> _event;
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;
            void createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager, std::size_t damage);

        public:
            InputSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize);
            ~InputSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // INPUTSYSTEM_HPP
