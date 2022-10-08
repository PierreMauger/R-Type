#ifndef GUISYSTEM_HPP
#define GUISYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"
#include "Includes.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace eng
{
    class GUISystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Clock _clock;
            bool _showEntity = true;
            bool _showEntityModify = false;
            std::size_t _entityID = 0;

            void drawEntity(ComponentManager &componentManager, EntityManager &entityManager);
            void drawModifyEntity(ComponentManager &componentManager, EntityManager &entityManager);
            void drawComponent(Component &component, std::type_index type, std::size_t id);

        public:
            GUISystem(std::shared_ptr<sf::RenderWindow> window);
            ~GUISystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
            std::string formatBool(std::size_t value, std::size_t size);
    };
}

#endif // GUISYSTEM_HPP
