#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

#include "ECS/System/ISystem.hpp"

namespace ECS
{
    class PhysicSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
        public:
            PhysicSystem(std::shared_ptr<sf::RenderWindow> window);
            ~PhysicSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // PHYSICSYSTEM_HPP
