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
        float x;
        float y;
} Size;

enum Priority {
    HIGH = 0,
    MEDIUM,
    LOW
};

typedef struct {
        std::size_t id;
        enum Priority priority;
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
        std::size_t life;
} Life;

typedef struct {
        bool enemy;
        float lastShoot;
        float shootDelay;
} Enemy;

typedef struct {
        bool app;
        float end;
} Appearance;

typedef struct {
        float speed;
} Speed;

typedef struct {
        float lastShoot;
        float shootDelay;
} CooldownShoot;

typedef struct {
        bool bar;
} CooldownBar;

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
