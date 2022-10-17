#ifndef VESSELPRELOAD_HPP
#define VESSELPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class VesselPreload : public EntityPreload
    {
        private:
            size_t _id;
            size_t _syncId;
        public:
            void preload(Engine &engine) override;
            void setSyncId(Engine &engine, std::size_t syncId);
            size_t getSyncId();
    };
}

#endif // VESSELPRELOAD_HPP
