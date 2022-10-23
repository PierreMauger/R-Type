#ifndef DEVOUREROFGODSPRELOAD_HPP
#define DEVOUREROFGODSPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class DevourerPreload : public EntityPreload
    {
        public:
            void preload(Engine &engine) override;
    };
}

#endif // DEVOUREROFGODSPRELOAD_HPP
