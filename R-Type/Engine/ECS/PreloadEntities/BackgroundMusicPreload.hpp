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
            void preload(Engine &engine) override;
    };
}

#endif // BACKGROUNDMUSICPRELOAD_HPP