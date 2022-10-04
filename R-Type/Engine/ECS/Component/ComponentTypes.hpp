#ifndef COMPONENTTYPES_HPP
#define COMPONENTTYPES_HPP

#include "Includes.hpp"

typedef struct {
        float x;
        float y;
        float z;
} Position;

typedef struct {
        float x;
        float y;
        float z;
} Velocity;

typedef struct {
        std::size_t id;
} SpriteID;

typedef struct {
        bool con;
} Controllable;

typedef struct {
        float speed;
} Speed;

typedef struct {
        sf::Clock clock;
        sf::Time time;
} CooldownShoot;

#endif // COMPONENTTYPES_HPP
