#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include "ECS/System/ISystem.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace ECS
{
    class InputSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Event> _event;
            std::shared_ptr<sf::Clock> _clock;

        public:
            InputSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock);
            ~InputSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // INPUTSYSTEM_HPP
