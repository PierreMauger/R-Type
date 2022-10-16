/**
 * @file ComponentTypes.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Ressources header containing the components' masks with their structs definitions.
 * @copyright Epitech Rennes 2022
 */

#ifndef COMPONENTTYPES_HPP
#define COMPONENTTYPES_HPP

/// @cond
#include "Includes.hpp"

/// @endcond

/**
 * @enum InfoComp
 * @brief Masks of the components.
 */
enum InfoComp {
    POS = 0b1,
    VEL = 0b10,
    SIZE = 0b100,
    SPRITEID = 0b1000,
    CONTROLLABLE = 0b10000,
    PARALLAX = 0b100000,
    PROJECTILE = 0b1000000,
    LIFE = 0b10000000,
    ENEMY = 0b100000000,
    APP = 0b1000000000,
    COOLDOWNSHOOT = 0b10000000000,
    COOLDOWNBAR = 0b100000000000,
    LIFEBAR = 0b1000000000000,
    PARENT = 0b10000000000000,
    PATERN = 0b100000000000000,
    SYNCID = 0b1000000000000000,
    DROP = 0b10000000000000000,
    TEXT = 0b100000000000000000,
    SOUNDID = 0b1000000000000000000,
};

/**
 * @struct Position
 * @brief The position component.
 */
typedef struct Position {
        float x;
        float y;
        float z;

        Position(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z)
        {
        }
} Position;

/**
 * @struct Velocity
 * @brief The velocity component.
 */
typedef struct Velocity {
        float x;
        float y;
        float z;
        float baseSpeed;

        Velocity(float x = 0.0f, float y = 0.0f, float z = 0.0f, float baseSpeed = 0.0) : x(x), y(y), z(z), baseSpeed(baseSpeed)
        {
        }
} Velocity;

/**
 * @struct Size
 * @brief The size component.
 */
typedef struct Size {
        float x;
        float y;

        Size(float x = 0.0f, float y = 0.0f) : x(x), y(y)
        {
        }
} Size;

/**
 * @enum Priority
 * @brief Priority of the sprites to be displayed (background before foreground etc..).
 */
enum Priority {
    HIGH = 0,
    MEDIUM,
    LOW
};

/**
 * @struct SpriteID
 * @brief The spriteID component.
 */
typedef struct SpriteID {
        std::size_t id;
        enum Priority priority;
        std::size_t curFrame;
        std::size_t nbFrame;
        bool signe;
        std::size_t offsetX;
        std::size_t offsetY;

        SpriteID(std::size_t i = 0, Priority prio = Priority::HIGH, std::size_t curFrame = 0, std::size_t nbFrame = 0, bool signe = false, std::size_t offsetX = 0,
                 std::size_t offsetY = 0)
            : id(i), priority(prio), curFrame(curFrame), nbFrame(nbFrame), signe(signe), offsetX(offsetX), offsetY(offsetY)
        {
        }
} SpriteID;

/**
 * @struct Controllable
 * @brief The controllable component.
 */
typedef struct Controllable {
        bool con;
        std::size_t kill;

        Controllable(bool con = true, std::size_t kill = 0) : con(con), kill(kill)
        {
        }
} Controllable;

/**
 * @struct Parallax
 * @brief The parallax component.
 */
typedef struct Parallax {
        bool par;

        Parallax(bool par = true) : par(par)
        {
        }
} Parallax;

/**
 * @struct Projectile
 * @brief The projectile component.
 */
typedef struct Projectile {
        bool proj;
        std::size_t damage;
        float size;

        Projectile(bool proj = true, std::size_t damage = 1, float size = 1) : proj(proj), damage(damage), size(size)
        {
        }
} Projectile;

/**
 * @struct Life
 * @brief The life component.
 */
typedef struct Life {
        std::size_t life;

        Life(std::size_t life = 1) : life(life)
        {
        }
} Life;

/**
 * @struct Enemy
 * @brief The enemy component.
 */
typedef struct Enemy {
        bool enemy;
        float lastShoot;
        float shootDelay;

        Enemy(bool enemy = false, float lastShoot = 0.0f, float shootDelay = 2.0f) : enemy(enemy), lastShoot(lastShoot), shootDelay(shootDelay)
        {
        }
} Enemy;

/**
 * @struct Appearance
 * @brief The appearance component.
 */
typedef struct Appearance {
        bool app;
        float end;

        Appearance(bool app = false, float end = 0.0f) : app(app), end(end)
        {
        }
} Appearance;

/**
 * @struct CooldownShoot
 * @brief The cooldownShoot component.
 */
typedef struct CooldownShoot {
        float lastShoot;
        float shootDelay;
        float size;

        CooldownShoot(float lastShoot = 0.0f, float shootDelay = 2.0f, std::size_t size = 1) : lastShoot(lastShoot), shootDelay(shootDelay), size(size)
        {
        }
} CooldownShoot;

/**
 * @struct CooldownBar
 * @brief The cooldownBar component.
 */
typedef struct CooldownBar {
        bool bar;

        CooldownBar(bool bar = false) : bar(bar)
        {
        }
} CooldownBar;

/**
 * @struct Lifebar
 * @brief The lifebar component.
 */
typedef struct LifeBar {
        bool bar;
        std::size_t lifeMax;

        LifeBar(bool bar = false, std::size_t lifeMax = 0) : bar(bar), lifeMax(lifeMax)
        {
        }
} LifeBar;

/**
 * @struct Parent
 * @brief The parent component.
 */
typedef struct Parent {
        std::size_t id;

        Parent(std::size_t i = 0) : id(i)
        {
        }
} Parent;

// Type dépendant du patern
/**
 * @enum TypePattern
 * @brief The type of pattern that an enemy has.
 */
enum TypePatern {
    LINE = 0,
    OSCILLATION,
    BIGOSCILLATION,
    CIRCLE
};

/**
 * @struct Patern
 * @brief The patern component.
 */
typedef struct Patern {
        enum TypePatern type;
        float angle;

        Patern(enum TypePatern type = TypePatern::LINE, float angle = 0.0f) : type(type), angle(angle)
        {
        }
} Patern;

/**
 * @struct SyncID
 * @brief The syncID component.
 */
typedef struct SyncID {
        std::size_t id;

        SyncID(std::size_t i = 0) : id(i)
        {
        }
} SyncID;

/**
 * @struct DropBonus
 * @brief The dropBonus component.
 */
typedef struct DropBonus {
        std::size_t id;

        DropBonus(std::size_t id = 0) : id(id)
        {
        }
} DropBonus;

/**
 * @struct Text
 * @brief The text component.
 */
typedef struct Text {
        sf::Text text;
        std::string str;

        Text(sf::Text text = sf::Text(), std::string str = "") : text(text), str(str)
        {
        }
} Text;

/**
 * @struct SoundID
 * @brief The soundID component.
 */
typedef struct SoundID {
        std::size_t id;
        bool play;
        bool loop;
        float pitch;

        SoundID(std::size_t id = 0, bool play = false, bool loop = false, float pitch = 1) : id(id), play(play), loop(loop), pitch(pitch)
        {
        }
} SoundID;

#endif // COMPONENTTYPES_HPP
