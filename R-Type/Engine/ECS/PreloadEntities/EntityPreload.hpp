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

            virtual void preload(Engine &engine) = 0;

            float createRandom(float min, float max)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(min, max);
                return dis(gen);
            }
    };
}

#endif // ENTITYPRELOAD_HPP
