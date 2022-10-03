#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "ECS/System/ISystem.hpp"
#include "ECS/System/Render/GUI.hpp"
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
            GUI _gui;

        public:
            RenderSystem();
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // RENDERSYSTEM_HPP
