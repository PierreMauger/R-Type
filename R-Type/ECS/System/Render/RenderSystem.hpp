#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "ECS/System/ISystem.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace ECS
{
    class RenderSystem : public virtual ISystem
    {
        private:
            sf::RenderWindow *_window;
            sf::Clock _clock;
            sf::Event _event;

        public:
            RenderSystem();
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager);
    };
}

#endif // RENDERSYSTEM_HPP
