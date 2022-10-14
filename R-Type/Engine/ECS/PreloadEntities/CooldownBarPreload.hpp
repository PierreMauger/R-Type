#ifndef COOLDOWNBARPRELOAD_HPP
#define COOLDOWNBARPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class CooldownBarPreload : public EntityPreload
    {
        public:
            void preload(Engine &engine, std::shared_ptr<std::vector<sf::Sprite>> sprites) override;
    };
}

#endif // COOLDOWNBARPRELOAD_HPP
