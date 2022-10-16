#ifndef SOUNDPRELOAD_HPP
#define SOUNDPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class SoundPreload : public EntityPreload
    {
        public:
            void preload(Engine &engine) override;
    };
}

#endif // SOUNDPRELOAD_HPP