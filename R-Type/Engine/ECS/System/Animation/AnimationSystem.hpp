#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

namespace eng
{
    class AnimationSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Event> _event;
            std::shared_ptr<sf::Clock> _clock;

        public:
            AnimationSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock);
            ~AnimationSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // ANIMATIONSYSTEM_HPP