#ifndef SCORETEXTPRELOAD_HPP
#define SCORETEXTPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class ScoreTextPreload : public EntityPreload
    {
        public:
            void preload(Engine &engine) override;
            void preloadScore(Engine &engine, std::size_t kill, std::size_t death);
    };
}

#endif // SCORETEXTPRELOAD_HPP
