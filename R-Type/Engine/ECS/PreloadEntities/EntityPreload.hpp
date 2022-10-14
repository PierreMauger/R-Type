#ifndef ENTITYPRELOAD_HPP
#define ENTITYPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/Engine.hpp"

namespace eng
{
    class EntityPreload
    {
        public:
            virtual ~EntityPreload() = default;

            virtual void preload(Engine &engine, std::shared_ptr<std::vector<sf::Sprite>> sprites) = 0;
    };
}

#endif // ENTITYPRELOAD_HPP
