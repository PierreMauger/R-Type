#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Loader/Loader.hpp"

namespace eng
{
    class AnimationSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Event> _event;
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<std::vector<sf::Sprite>> _sprites;
            std::map<std::size_t, float> _lastTime;
            std::map<std::size_t, float> _delay;

        public:
            AnimationSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::Sprite>> sprites);
            ~AnimationSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // ANIMATIONSYSTEM_HPP