#ifndef COMPONENTTYPES_HPP
#define COMPONENTTYPES_HPP

#include "Includes.hpp"

typedef struct Position {
        float x;
        float y;
        float z;

        Position(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
} Position;

typedef struct Velocity {
        float x;
        float y;
        float z;

        Velocity(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
} Velocity;

typedef struct SpriteID {
        std::size_t id;

        SpriteID(std::size_t i = 0) : id(i) {}
} SpriteID;

typedef struct Controllable {
        bool con;

        Controllable(bool con = true) : con(con) {}
} Controllable;

typedef struct Parallax {
        bool par;

        Parallax(bool par = true) : par(par) {}
} Parallax;

typedef struct Speed {
        float speed;

        Speed(float spd = 0.0f) : speed(spd) {}
} Speed;

typedef struct CooldownShoot {
        float time;
        float cooldown;

        CooldownShoot(float t = 0.0f, float cd = 1.0f) : time(t), cooldown(cd) {}
} CooldownShoot;

typedef struct Parent {
        std::size_t id;

        Parent(std::size_t i = 0) : id(i) {}
} Parent;

#endif // COMPONENTTYPES_HPP
