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
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @enum InfoComp
     * @brief Masks of the components.
     */
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
        PATTERN = 1 << 15,
        SYNCID = 1 << 16,
        DROP = 1 << 17,
        TEXT = 1 << 18,
        SOUNDID = 1 << 19,
        SPRITEAT = 1 << 20,
        BUTTON = 1 << 21,
        CHILD = 1 << 22,
    };
}

/**
 * @struct Position
 * @brief The position component.
 */
typedef struct Position {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
} Position;

/**
 * @struct Velocity
 * @brief The velocity component.
 */
typedef struct Velocity {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float baseSpeedX = 0.0f;
        float baseSpeedY = 0.0f;
} Velocity;

/**
 * @struct Size
 * @brief The size component.
 */
typedef struct Size {
        float x = 0.0f;
        float y = 0.0f;
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
        std::size_t id = 0;
        Priority priority = Priority::MEDIUM;
        std::size_t curFrame = 0;
        std::size_t nbFrame = 0;
        bool autoLoop = false;
        bool sign = false;
        float lastTime = 0.0f;
        float delay = 0.0f;
        std::size_t offsetX = 0;
        std::size_t offsetY = 0;
} SpriteID;

/**
 * @struct Controllable
 * @brief The controllable component.
 */
typedef struct Controllable {
        bool con = false;
        std::size_t kill = 0;
        std::size_t death = 0;
} Controllable;

/**
 * @struct Parallax
 * @brief The parallax component.
 */
typedef struct Parallax {
        bool par = true;
} Parallax;

/**
 * @struct Projectile
 * @brief The projectile component.
 */
typedef struct Projectile {
        bool proj = true;
        std::size_t damage = 1;
        float size = 1.0f;
} Projectile;

/**
 * @struct Life
 * @brief The life component.
 */
typedef struct Life {
        std::size_t defaultLife = 1;
        std::size_t life = defaultLife;
} Life;

/**
 * @struct Enemy
 * @brief The enemy component.
 */
typedef struct Enemy {
        bool enemy = false;
} Enemy;

/**
 * @struct Appearance
 * @brief The appearance component.
 */
typedef struct Appearance {
        bool app = false;
        float end = 0.0f;
        float x_app = 0.0f;
} Appearance;

/**
 * @struct Disappearance
 * @brief The disappearance component.
 */
typedef struct Disappearance {
        bool dis = false;
        float end = 0.0f;
} Disappearance;

/**
 * @struct CooldownShoot
 * @brief The cooldownShoot component.
 */
typedef struct CooldownShoot {
        float lastShoot = 0.0f;
        float shootDelay = 2.0f;
        float size = 1.0f;
} CooldownShoot;

/**
 * @struct CooldownBar
 * @brief The cooldownBar component.
 */
typedef struct CooldownBar {
        bool bar = false;
} CooldownBar;

/**
 * @struct Lifebar
 * @brief The lifebar component.
 */
typedef struct LifeBar {
        bool bar = false;
        std::size_t lifeMax = 1;
} LifeBar;

/**
 * @struct Parent
 * @brief The parent component.
 */
typedef struct Parent {
        std::size_t id = 0;
        bool follow = false;
} Parent;

// Type dépendant du patern
/**
 * @enum TypePattern
 * @brief The type of pattern that an enemy has.
 */
enum TypePattern {
    LINE = 0,
    OSCILLATION,
    BIGOSCILLATION,
    CIRCLE,
    DEVOUREROSC,
    CTHULHU
};

/**
 * @enum TypeStatus
 * @brief The type of status that an enemy has.
 */
enum TypeStatus {
    IDLE = 0,
    MOVE,
    SEARCH,
    ATTACK,
    SHOOT,
    TRANSFORM
};

/**
 * @enum TypePhase
 * @brief The type of phase that an enemy has.
 */
enum TypePhase {
    PHASE01 = 0,
    PHASE02,
    PHASE03
};

/**
 * @struct Pattern
 * @brief The patern component.
 */
typedef struct Pattern {
        enum TypePattern type = TypePattern::LINE;
        enum TypeStatus status = TypeStatus::IDLE;
        enum TypePhase phase = TypePhase::PHASE01;
        float angle = 0.0f;
        float statusTime = 0.0f;
        size_t focusEntity = 0;
        size_t phaseCount = 0;
        Position lastPosFocus = {0.0f, 0.0f, 0.0f};
} Pattern;

/**
 * @struct SyncID
 * @brief The syncID component.
 */
typedef struct SyncID {
        std::size_t id = 0;
} SyncID;

/**
 * @struct DropBonus
 * @brief The dropBonus component.
 */
typedef struct DropBonus {
        std::size_t id = 0;
} DropBonus;

/**
 * @struct Text
 * @brief The text component.
 */
typedef struct Text {
        std::string str = "";
        bool hasValue = true;
        std::size_t value = 0;
        sf::Vector2f pos = {0.0f, 0.0f};
} Text;

/**
 * @struct SoundID
 * @brief The soundID component.
 */
typedef struct SoundID {
        std::size_t id = 0;
        bool play = false;
        bool loop = false;
        float pitch = 1.0f;
} SoundID;

/**
 * @struct SpriteAttribut
 * @brief The spriteAttribut component.
 */
typedef struct SpriteAttribut {
        float rotation = 0;
        sf::FloatRect rect = sf::FloatRect();
        sf::Color color = sf::Color::White;
        sf::Vector2f scale = {1.0f, 1.0f};
        sf::Vector2f offset = {0.0f, 0.0f};
} SpriteAttribut;

enum ButtonType {
    QUIT = 0,
    PLAY,
    BACK,
};

typedef struct Button {
        ButtonType type = QUIT;
} Button;

typedef struct Child {
        std::size_t id = 0;
} Child;

#endif // COMPONENTTYPES_HPP
