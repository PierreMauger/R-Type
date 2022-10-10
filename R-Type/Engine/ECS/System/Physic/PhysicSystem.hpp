#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"

namespace eng
{
    class PhysicSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            bool collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos);
            bool collisionFireball(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position &pos);

        public:
            PhysicSystem(std::shared_ptr<sf::RenderWindow> window);
            ~PhysicSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // PHYSICSYSTEM_HPP
