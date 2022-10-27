#ifndef PROJECTILEPRELOAD_HPP
#define PROJECTILEPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class ProjectilePreload : public EntityPreload
    {
        public:
            static void preload(Engine &engine);
            static void createShoot(EntityManager &entityManager, ComponentManager &componentManager, sf::Vector2u windowsSize,
                                    std::shared_ptr<sf::Vector2f> screenSize, std::size_t id, std::size_t damage);
    };
}

#endif // PROJECTILEPRELOAD_HPP
