#ifndef BACKGROUNDMUSICPRELOAD_HPP
#define BACKGROUNDMUSICPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class BackgroundMusicPreload : public EntityPreload
    {
        public:
            static void preload(Engine &engine);
    };
}

#endif // BACKGROUNDMUSICPRELOAD_HPP
