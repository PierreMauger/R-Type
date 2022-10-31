#ifndef PARALLAXPRELOAD_HPP
#define PARALLAXPRELOAD_HPP

#include <Includes.hpp>

#include "Engine.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class ParallaxPreload : public EntityPreload
    {
        public:
            static void preload(Engine &engine);
            static void preload(ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize);
    };
}

#endif // PARALLAXPRELOAD_HPP
