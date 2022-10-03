#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

#include "ECS/System/ISystem.hpp"

namespace ECS
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
