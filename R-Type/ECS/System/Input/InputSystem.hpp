#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include "ECS/System/ISystem.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

namespace ECS
{
    class InputSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Event> _event;

        public:
            InputSystem(sf::Event &event);
            ~InputSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // INPUTSYSTEM_HPP
