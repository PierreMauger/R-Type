#ifndef PATERNSYSTEM_HPP
#define PATERNSYSTEM_HPP

#include "Engine/ECS/System/ISystem.hpp"

namespace eng
{
    class PaternSystem : public virtual ISystem
    {
        private:
        public:
            PaternSystem();
            ~PaternSystem() = default;
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // PATERNSYSTEM_HPP