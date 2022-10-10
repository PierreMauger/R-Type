#ifndef PARALLAX_HPP
#define PARALLAX_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class Vessel : public EntityPreload
    {
        public:
            void preload(EntityManager &entityManager, ComponentManager &componentManager) override;
    };
}

#endif // PARALLAX_HPP
