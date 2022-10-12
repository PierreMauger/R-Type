#ifndef ENEMYSYSTEM_HPP
#define ENEMYSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"

#define RADIUS 50
#define SPEED_OSC 6

namespace eng
{
    class EnemySystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::Clock> _clock;
            void createShoot(std::size_t id, ComponentManager &componentManager, Position pos, EntityManager &entityManager);

        public:
            EnemySystem(std::shared_ptr<sf::Clock> clock);
            ~EnemySystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // ENEMYSYSTEM_HPP
