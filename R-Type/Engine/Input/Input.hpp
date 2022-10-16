#ifndef INPUT_HPP
#define INPUT_HPP

#include "ECS/Component/ComponentManager.hpp"
#include "ECS/Entity/EntityManager.hpp"
#include "Includes.hpp"

namespace eng
{
    class Input
    {
        private:
        public:
            Input();
            ~Input() = default;
            void checkInput(std::size_t id, sf::Keyboard::Key input, ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<sf::Clock> clock);
            void createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager, std::size_t damage);
    };
}

#endif // INPUT_HPP