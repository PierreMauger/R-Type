#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "ECS/System/ISystem.hpp"
#include "Includes.hpp"

namespace ECS
{
    class RenderSystem : public virtual ISystem
    {
        private:
            std::size_t id;
            std::shared_ptr<sf::RenderWindow> _window;
            std::array<sf::Texture, 5> _texture; // array car sf::vector stock dans la mémoire de manière bizarre donc white square problem sfml
            std::vector<sf::Sprite> _sprites;

        public:
            RenderSystem(std::shared_ptr<sf::RenderWindow> window);
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager);
    };
}

#endif // RENDERSYSTEM_HPP
