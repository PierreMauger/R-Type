#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>

#include "Engine/ECS/System/ISystem.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace eng
{
    class GUI
    {
        private:
            bool _showEntityGUI = false;
            std::size_t _entityID = 0;

        public:
            GUI(std::shared_ptr<sf::RenderWindow> window);
            ~GUI() = default;
            void drawGUI(ComponentManager &componentManager, EntityManager &entityManager);
            void drawEntityGUI(ComponentManager &componentManager, EntityManager &entityManager);
            void drawComponentGUI(Component &component, std::type_index type, std::size_t id);
    };
}

#endif // GUI_HPP
