#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/System/ISystem.hpp"

namespace eng
{
    class ScoreSystem : public virtual ISystem
    {
        private:
            bool findVessel(ComponentManager &componentManager, EntityManager &entityManager, Controllable &Controllable);

        public:
            ScoreSystem();
            ~ScoreSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // SCORESYSTEM_HPP