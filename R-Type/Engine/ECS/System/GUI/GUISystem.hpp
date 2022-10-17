/**
 * @file GUISystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System of the GUI (Game User Interface).
 * @copyright Epitech Rennes 2022
*/

#ifndef GUISYSTEM_HPP
#define GUISYSTEM_HPP

/// @cond
#include "Engine/ECS/System/ISystem.hpp"
#include "Includes.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
/// @endcond

#define FORMAT_NAME(name) name + std::to_string(std::stoi(name)).length()

/**
 * @brief Engine namespace.
 * @namespace eng
*/
namespace eng
{
    /**
     * @brief System of the GUI.
     * @class GUISystem
    */
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
            /**
             * @brief GUISystem constructor.
             * @fn GUISystem(std::shared_ptr<sf::RenderWindow> window)
             * @param window A shared pointer to the SFML render window.
            */
            GUISystem(std::shared_ptr<sf::RenderWindow> window);
            /**
             * @brief GUISystem destructor.
             * @fn ~GUISystem
            */
            ~GUISystem();
            /**
             * @brief Update the GUI system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
            */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // GUISYSTEM_HPP
