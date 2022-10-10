#ifndef COMPONENTTYPES_HPP
#define COMPONENTTYPES_HPP

#include "Includes.hpp"

typedef struct Position {
        float x;
        float y;
        float z;

        Position(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z)
        {
        }
} Position;

typedef struct Velocity {
        float x;
        float y;
        float z;

        Velocity(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z)
        {
        }
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

typedef struct SpriteID {
        std::size_t id;
        enum Priority priority;

        SpriteID(std::size_t i = 0, Priority prio = Priority::HIGH) : id(i), priority(prio)
        {
        }
} SpriteID;

typedef struct Controllable {
        bool con;

        Controllable(bool con = true) : con(con)
        {
        }
} Controllable;

typedef struct Parallax {
        bool par;

        Parallax(bool par = true) : par(par)
        {
        }
} Parallax;

typedef struct Projectile {
        bool proj;

        Projectile(bool proj = true) : proj(proj)
        {
        }
} Projectile;

typedef struct Life {
        std::size_t life;

        Life(std::size_t life = 1) : life(life)
        {
        }
} Life;

typedef struct Enemy {
        bool enemy;
        float lastShoot;
        float shootDelay;

        Enemy(bool enemy = false, float lastShoot = 0.0f, float shootDelay = 2.0f) : enemy(enemy), lastShoot(lastShoot), shootDelay(shootDelay)
        {
        }
} Enemy;

typedef struct Appearance {
        bool app;
        float end;

        Appearance(bool app = false, float end = 0.0f) : app(app), end(end)
        {
        }
} Appearance;

typedef struct Speed {
        float speed;

        Speed(float spd = 0.0f) : speed(spd)
        {
        }
} Speed;

typedef struct CooldownShoot {
        float lastShoot;
        float shootDelay;

        CooldownShoot(float lastShoot = 0.0f, float shootDelay = 2.0f) : lastShoot(lastShoot), shootDelay(shootDelay)
        {
        }
} CooldownShoot;

typedef struct CooldownBar {
        bool bar;

        CooldownBar(bool bar = false) : bar(bar)
        {
        }
} CooldownBar;

typedef struct LifeBar {
        bool bar;
        std::size_t lifeMax;

        LifeBar(bool bar = false, std::size_t lifeMax = 0) : bar(bar), lifeMax(lifeMax)
        {
        }
} LifeBar;

typedef struct Parent {
        std::size_t id;

        Parent(std::size_t i = 0) : id(i)
        {
        }
} Parent;

// Type dépendant du patern
enum TypePatern {
    LINE = 0,
    OSCILLATION,
    BIGOSCILLATION,
    CIRCLE
};

typedef struct Patern {
        enum TypePatern type;
        float angle;
        sf::Vector2f center;

        Patern(enum TypePatern type = TypePatern::LINE, float angle = 0.0f, sf::Vector2f center = sf::Vector2f(0.0f, 0.0f)) : type(type), angle(angle), center(center)
        {
        }
} Patern;

#endif // COMPONENTTYPES_HPP
