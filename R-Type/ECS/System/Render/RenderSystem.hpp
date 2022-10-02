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

            bool _showEntityGUI = false;
            std::size_t _entityID = 0;

        public:
            RenderSystem();
            ~RenderSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
            void drawGUI(ComponentManager &componentManager, EntityManager &entityManager);
            void drawEntityGUI(ComponentManager &componentManager, EntityManager &entityManager, std::size_t id);
    };
}

#endif // RENDERSYSTEM_HPP
