#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "ECS/System/ISystem.hpp"

namespace ECS
{
    class RenderSystem : public virtual ISystem
    {
        private:
            std::size_t id;
            sf::RenderWindow *window;

        public:
            RenderSystem();
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager);
    };
}

#endif // RENDERSYSTEM_HPP
