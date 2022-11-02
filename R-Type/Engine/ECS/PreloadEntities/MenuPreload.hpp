#ifndef MENUPRELOAD_HPP
#define MENUPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class MenuPreload : public EntityPreload
    {
        public:
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager);
    };
}

#endif // MENUPRELOAD_HPP
