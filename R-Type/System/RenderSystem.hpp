#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "System/ISystem.hpp"

namespace ECS
{
    class RenderSystem : public virtual ISystem
    {
        private:
            std::size_t id;

        public:
            RenderSystem();
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager);
    };
}

#endif // RENDERSYSTEM_HPP
