#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "ECS/System/ISystem.hpp"

namespace ECS
{
    class RenderSystem : public virtual ISystem
    {
        private:
            std::size_t id;
            std::shared_ptr<sf::RenderWindow> window;

        public:
            RenderSystem(std::shared_ptr<sf::RenderWindow> window);
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager);
    };
}

#endif // RENDERSYSTEM_HPP
