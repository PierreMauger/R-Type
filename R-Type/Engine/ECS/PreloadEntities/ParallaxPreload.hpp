#ifndef PARALLAXPRELOAD_HPP
#define PARALLAXPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class ParallaxPreload : public EntityPreload
    {
        public:
            static void preload(Engine &engine);
    };
}

#endif // PARALLAXPRELOAD_HPP
