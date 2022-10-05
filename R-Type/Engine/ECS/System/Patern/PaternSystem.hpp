#ifndef PATERNSYSTEM_HPP
#define PATERNSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"

#define RADIUS 50
#define SPEED_OSC 6

namespace eng
{
    class PaternSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Clock> _clock;
            float _angle;

        public:
            PaternSystem(std::shared_ptr<sf::Clock> clock);
            ~PaternSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // PATERNSYSTEM_HPP