#ifndef MODELIDSYSTEM_HPP
#define MODELIDSYSTEM_HPP

#include "System/ISystem.hpp"

namespace ECS
{
    class ModelIdSystem : public virtual ISystem
    {
        private:
            std::size_t id;

        public:
            ModelIdSystem();
            ~ModelIdSystem() = default;
            void update(ComponentManager &componentManager) override;
    };
}

#endif // MODELIDSYSTEM_HPP
