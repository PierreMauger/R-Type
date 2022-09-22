#include "ASystem.hpp"

namespace ECS
{
    class PhysicsSystem : public virtual ASystem
    {
        private:
        public:
            PhysicsSystem();
            ~PhysicsSystem() = default;
            void update(ComponentManager componentManager) override;
    };
}