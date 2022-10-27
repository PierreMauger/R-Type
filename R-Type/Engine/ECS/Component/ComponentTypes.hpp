#ifndef COMPONENTTYPES_HPP
#define COMPONENTTYPES_HPP

#include "Includes.hpp"

namespace eng
{
    enum InfoComp {
        POS = 1 << 0,
        VEL = 1 << 1,
        SIZE = 1 << 2,
        SPRITEID = 1 << 3,
        CONTROLLABLE = 1 << 4,
        PARALLAX = 1 << 5,
        PROJECTILE = 1 << 6,
        LIFE = 1 << 7,
        ENEMY = 1 << 8,
        APP = 1 << 9,
        DIS = 1 << 10,
        COOLDOWNSHOOT = 1 << 11,
        COOLDOWNBAR = 1 << 12,
        LIFEBAR = 1 << 13,
        PARENT = 1 << 14,
        PATERN = 1 << 15,
        SYNCID = 1 << 16,
        DROP = 1 << 17,
        TEXT = 1 << 18,
        SOUNDID = 1 << 19,
        SPRITEAT = 1 << 20,
        BUTTON = 1 << 21,
    };
}

typedef struct {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
} Position;

typedef struct {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float baseSpeedX = 0.0f;
        float baseSpeedY = 0.0f;
} Velocity;

typedef struct {
        float x = 0.0f;
        float y = 0.0f;
} Size;

enum Priority {
    HIGH = 0,
    MEDIUM,
    LOW
};

typedef struct {
        std::size_t id = 0;
        enum Priority priority = Priority::HIGH;
        std::size_t curFrame = 0;
        std::size_t nbFrame = 0;
        bool sign = false;
        float lastTime = 0.0f;
        float delay = 0.0f;
        std::size_t offsetX = 0;
        std::size_t offsetY = 0;
} SpriteID;

typedef struct {
        bool con = false;
        std::size_t kill = 0;
        std::size_t death = 0;
} Controllable;

typedef struct {
        bool par = true;
} Parallax;

typedef struct {
        bool proj = true;
        std::size_t damage = 1;
        float size = 1.0f;
} Projectile;

typedef struct {
        std::size_t life = 1;
} Life;

typedef struct {
        bool enemy = false;
        float lastShoot = 0.0f;
        float shootDelay = 2.0f;
} Enemy;

typedef struct {
        bool app = false;
        float end = 0.0f;
} Appearance;

typedef struct {
        bool dis = false;
        float end = 0.0f;
} Disappearance;

typedef struct {
        float lastShoot = 0.0f;
        float shootDelay = 2.0f;
        float size = 1.0f;
} CooldownShoot;

typedef struct {
        bool bar = false;
} CooldownBar;

typedef struct {
        bool bar = false;
        std::size_t lifeMax = 1;
} LifeBar;

typedef struct {
        std::size_t id = 0;
} Parent;

// Type dépendant du patern
enum TypePatern {
    LINE = 0,
    OSCILLATION,
    BIGOSCILLATION,
    CIRCLE
};

typedef struct {
        TypePatern type = LINE;
        float angle = 0.0f;
} Patern;

typedef struct {
        std::size_t id = 0;
} SyncID;

typedef struct {
        std::size_t id = 0;
} DropBonus;

typedef struct {
        std::string str = "";
        bool hasValue = true;
        std::size_t value = 0;
        sf::Vector2f pos = {0.0f, 0.0f};
} Text;

typedef struct {
        std::size_t id = 0;
        bool play = false;
        bool loop = false;
        float pitch = 1.0f;
} SoundID;

typedef struct {
        float rotation = 0;
        sf::FloatRect rect = sf::FloatRect();
        sf::Color color = sf::Color::White;
        sf::Vector2f scale = {1.0f, 1.0f};
} SpriteAttribut;

enum ButtonType {
        QUIT = 0,
        PLAY,
        BACK,
};

typedef struct {
        ButtonType type = QUIT;
} Button;

#endif // COMPONENTTYPES_HPP
