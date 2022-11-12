/**
 * @file ClickSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System that handle mouse inputs.
 * @copyright Epitech Rennes 2022
 */

#ifndef CLICKSYSTEM_HPP
#define CLICKSYSTEM_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Graphic/Graphic.hpp"
/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief System that handle mouse inputs.
     * @class ClickSystem
     */
    class ClickSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;
            std::shared_ptr<sf::Event> _event;
            std::shared_ptr<std::size_t> _sceneId;
            std::shared_ptr<std::size_t> _port;
            std::shared_ptr<std::string> _ip;
            std::shared_ptr<bool> _isLocal;
            std::shared_ptr<std::size_t> _syncId;

            std::size_t _buttonTag = (InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT | InfoComp::SIZE);
            std::size_t _sceneTag = (InfoComp::SCENE);

        public:
            /**
             * @brief ClickSystem constructor.
             * @fn ClickSystem(Graphic &graphic, std::shared_ptr<std::size_t> port, std::shared_ptr<std::string> ip, std::shared_ptr<bool> isLocal, std::shared_ptr<std::size_t> syncId, EntityManager &entityManager)
             * @param graphic A reference to the Graphic
             * @param port A shared pointer to the port
             * @param ip A shared pointer to the ip
             * @param isLocal A shared pointer to the boolean representing if the client is playing in local or online
             * @param syncId The synchronized id of the client
             * @param entityManager A reference to the EntityManager
             */
            ClickSystem(Graphic &graphic, std::shared_ptr<std::size_t> port, std::shared_ptr<std::string> ip, std::shared_ptr<bool> isLocal, std::shared_ptr<std::size_t> syncId, EntityManager &entityManager);
            /**
             * @brief ClickSystem destructor.
             * @fn ~ClickSystem()
             */
            ~ClickSystem() = default;
            /**
             * @brief Update the click system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
             */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // CLICKSYSTEM_HPP
