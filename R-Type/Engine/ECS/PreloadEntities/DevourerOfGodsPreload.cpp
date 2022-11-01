#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"

void eng::DevourerPreload::preload(Engine &engine)
{
    ComponentManager &componentManager = engine.getECS().getComponentManager();
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();
    std::size_t lastId = 0;
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN | InfoComp::COOLDOWNACT | InfoComp::DROP),
        engine.getECS().getComponentManager());

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{16, Priority::LOW});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(id, SpriteAttribut{0, {0, 0, 375, 311}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{530 / screenSize->x * windowsSize.x, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern::DEVOUREROSC, 0, 500});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{(375 * 0.5f) / screenSize->x * windowsSize.x, (331 * 0.5f) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(GroupEntity)).emplaceData(id, GroupEntity{0, 20, 0, 9, {530 / screenSize->x * windowsSize.x, 0}});
    componentManager.getComponent(typeid(CooldownAction)).emplaceData(id, CooldownAction{0, 0.5, {}});
    componentManager.getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{1});

    lastId = id;
    for (std::size_t i = 0, newId = 0, sizeyDiff = 10; i < 8; i++) {
        Position pos = componentManager.getSingleComponent<Position>(lastId);
        Size size = componentManager.getSingleComponent<Size>(lastId);
        newId = engine.getECS().getEntityManager().addMask(
            (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN | InfoComp::PARENT | InfoComp::COOLDOWNSHOOT),
            engine.getECS().getComponentManager());
        componentManager.getComponent(typeid(SpriteID)).emplaceData(newId, SpriteID{15, Priority::LOW});
        componentManager.getComponent(typeid(SpriteAttribut))
            .emplaceData(newId, SpriteAttribut{0, {0, 0, 187, 282}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(newId, Position{pos.x + size.x, pos.y + sizeyDiff, 0});
        componentManager.getComponent(typeid(Velocity)).emplaceData(newId, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
        componentManager.getComponent(typeid(Enemy)).emplaceData(newId, Enemy{true});
        componentManager.getComponent(typeid(Pattern)).emplaceData(newId, Pattern{TypePattern::DEVOUREROSC, 0});
        componentManager.getComponent(typeid(Size)).emplaceData(newId, Size{(187 * 0.5f) / screenSize->x * windowsSize.x, (282 * 0.5f) / screenSize->y * windowsSize.y});
        componentManager.getComponent(typeid(GroupEntity)).emplaceData(newId, GroupEntity{0, 20, i + 1, 9, {pos.x + size.x, pos.y + sizeyDiff}});
        componentManager.getComponent(typeid(Parent)).emplaceData(newId, Parent{lastId});
        componentManager.getComponent(typeid(CooldownShoot)).emplaceData(newId, CooldownShoot{0, 1.0f + (static_cast<float>(i) / 10.f)});
        lastId = newId;
        sizeyDiff = 0;
    }
    Position &pos = componentManager.getSingleComponent<Position>(lastId);
    std::size_t newId = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN | InfoComp::PARENT),
        engine.getECS().getComponentManager());
    componentManager.getComponent(typeid(SpriteID)).emplaceData(newId, SpriteID{17, Priority::LOW});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(newId, SpriteAttribut{0, {0, 0, 237, 256}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(newId, Position{pos.x + 187 * 0.5f, pos.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(newId, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(newId, Enemy{true});
    componentManager.getComponent(typeid(Pattern)).emplaceData(newId, Pattern{TypePattern::DEVOUREROSC, 0});
    componentManager.getComponent(typeid(Size)).emplaceData(newId, Size{(237 * 0.5f) / screenSize->x * windowsSize.x, (256 * 0.5f) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(GroupEntity)).emplaceData(newId, GroupEntity{0, 20, 9, 9, {pos.x + 187 * 0.5f, pos.y}});
    componentManager.getComponent(typeid(Parent)).emplaceData(newId, Parent{lastId});
}

void eng::DevourerPreload::preload(Engine &engine, float x, float y)
{
    ComponentManager &componentManager = engine.getECS().getComponentManager();
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();
    std::size_t lastId = 0;
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN | InfoComp::COOLDOWNACT | InfoComp::DROP),
        engine.getECS().getComponentManager());

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{16, Priority::LOW});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(id, SpriteAttribut{0, {0, 0, 375, 311}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{x / screenSize->x * windowsSize.x, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern::DEVOUREROSC, 0, 500});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{(375 * 0.5f) / screenSize->x * windowsSize.x, (331 * 0.5f) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(GroupEntity)).emplaceData(id, GroupEntity{0, 20, 0, 9, {530 / screenSize->x * windowsSize.x, 0}});
    componentManager.getComponent(typeid(CooldownAction)).emplaceData(id, CooldownAction{0, 0.5, {}});
    componentManager.getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{1});

    lastId = id;
    for (std::size_t i = 0, newId = 0, sizeyDiff = 10; i < 8; i++) {
        Position pos = componentManager.getSingleComponent<Position>(lastId);
        Size size = componentManager.getSingleComponent<Size>(lastId);
        newId = engine.getECS().getEntityManager().addMask(
            (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN | InfoComp::PARENT | InfoComp::COOLDOWNSHOOT),
            engine.getECS().getComponentManager());
        componentManager.getComponent(typeid(SpriteID)).emplaceData(newId, SpriteID{15, Priority::LOW});
        componentManager.getComponent(typeid(SpriteAttribut))
            .emplaceData(newId, SpriteAttribut{0, {0, 0, 187, 282}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(newId, Position{pos.x + size.x, pos.y + sizeyDiff, 0});
        componentManager.getComponent(typeid(Velocity)).emplaceData(newId, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
        componentManager.getComponent(typeid(Enemy)).emplaceData(newId, Enemy{true});
        componentManager.getComponent(typeid(Pattern)).emplaceData(newId, Pattern{TypePattern::DEVOUREROSC, 0});
        componentManager.getComponent(typeid(Size)).emplaceData(newId, Size{(187 * 0.5f) / screenSize->x * windowsSize.x, (282 * 0.5f) / screenSize->y * windowsSize.y});
        componentManager.getComponent(typeid(GroupEntity)).emplaceData(newId, GroupEntity{0, 20, i + 1, 9, {pos.x + size.x, pos.y + sizeyDiff}});
        componentManager.getComponent(typeid(Parent)).emplaceData(newId, Parent{lastId});
        componentManager.getComponent(typeid(CooldownShoot)).emplaceData(newId, CooldownShoot{0, 1.0f + (static_cast<float>(i) / 10.f)});
        lastId = newId;
        sizeyDiff = 0;
    }
    Position &pos = componentManager.getSingleComponent<Position>(lastId);
    std::size_t newId = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN | InfoComp::PARENT),
        engine.getECS().getComponentManager());
    componentManager.getComponent(typeid(SpriteID)).emplaceData(newId, SpriteID{17, Priority::LOW});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(newId, SpriteAttribut{0, {0, 0, 237, 256}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(newId, Position{pos.x + 187 * 0.5f, pos.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(newId, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(newId, Enemy{true});
    componentManager.getComponent(typeid(Pattern)).emplaceData(newId, Pattern{TypePattern::DEVOUREROSC, 0});
    componentManager.getComponent(typeid(Size)).emplaceData(newId, Size{(237 * 0.5f) / screenSize->x * windowsSize.x, (256 * 0.5f) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(GroupEntity)).emplaceData(newId, GroupEntity{0, 20, 9, 9, {pos.x + 187 * 0.5f, pos.y}});
    componentManager.getComponent(typeid(Parent)).emplaceData(newId, Parent{lastId});
}
