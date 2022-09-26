#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "System/ISystem.hpp"

namespace ECS
{
    class PhysicsSystem : public virtual ISystem
    {
        private:
        public:
            PhysicsSystem();
            ~PhysicsSystem() = default;
            void update(ComponentManager componentManager) override;
    };
}

#endif // PHYSICSSYSTEM_HPP
