#ifndef VESSELPRELOAD_HPP
#define VESSELPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class VesselPreload : public EntityPreload
    {
        public:
            void preload(Engine &engine) override;
            static void preloadScore(EntityManager &entityManager, ComponentManager &componentManager, std::size_t kill, std::size_t death, sf::Vector2u windowsSize,
                                     std::shared_ptr<sf::Vector2f> screenSize);
    };
}

#endif // VESSELPRELOAD_HPP
