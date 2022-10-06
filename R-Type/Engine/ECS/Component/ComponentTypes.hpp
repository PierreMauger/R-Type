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
        std::size_t prio;
} SpriteID;

typedef struct {
        bool con;
} Controllable;

typedef struct {
        bool par;
} Parallax;

typedef struct {
        bool proj;
} Projectile;

typedef struct {
        bool enemy;
} Enemy;

typedef struct {
        float speed;
} Speed;

typedef struct {
        float time;
        float cooldown;
} CooldownShoot;

typedef struct {
        std::size_t id;
} Parent;

// Type dépendant du patern
enum TypePatern {
    LINE = 0,
    OSCILLATION,
    BIGOSCILLATION
};

typedef struct {
        enum TypePatern type;
        float angle;
        float center;
} Patern;

#endif // COMPONENTTYPES_HPP
