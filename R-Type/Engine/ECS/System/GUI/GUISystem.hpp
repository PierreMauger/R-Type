#ifndef GUISYSTEM_HPP
#define GUISYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"
#include "Includes.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

#define FORMAT_NAME(name) name + std::to_string(std::stoi(name)).length()

namespace eng
{
    class GUISystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            sf::Clock _clock;
            bool _showEntityManager = true;
            bool _showEntityDetails = false;
            std::size_t _selectedEntity = 0;

            void drawEntityManager(ComponentManager &componentManager, EntityManager &entityManager);
            void drawEntityDetails(ComponentManager &componentManager, EntityManager &entityManager);
            void drawEntityComponent(ComponentManager &componentManager, std::size_t type);
            std::string formatBool(std::size_t value, std::size_t size);

        public:
            GUISystem(std::shared_ptr<sf::RenderWindow> window);
            ~GUISystem();
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // GUISYSTEM_HPP
