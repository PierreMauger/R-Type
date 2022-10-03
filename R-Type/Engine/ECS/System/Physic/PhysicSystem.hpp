#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"

namespace eng
{
    class PhysicSystem : public virtual ISystem
    {
        private:
        public:
            PhysicSystem();
            ~PhysicSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // PHYSICSYSTEM_HPP
