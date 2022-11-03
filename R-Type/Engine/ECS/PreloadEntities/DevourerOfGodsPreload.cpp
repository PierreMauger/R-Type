#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"

using namespace eng;

void DevourerPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    std::size_t lastId = 0;
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{17, Priority::LOW});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 375, 311}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x + 80), 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern::DEVOUREROSC, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{(375 * 0.5f) / screenSize->x * windowsSize.x, (331 * 0.5f) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(GroupEntity)).emplaceData(id, GroupEntity{0, 10, 0, 11, {static_cast<float>(windowsSize.x + 80), static_cast<float>(windowsSize.y) / 2}});

    lastId = id;
    for (std::size_t i = 0, newId = 0, sizeyDiff = 10; i < 10; i++) {
        Position pos = componentManager.getSingleComponent<Position>(lastId);
        Size size = componentManager.getSingleComponent<Size>(lastId);
        newId = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN | InfoComp::PARENT), componentManager);
        componentManager.getComponent(typeid(SpriteID)).emplaceData(newId, SpriteID{16, Priority::LOW});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(newId, SpriteAttribut{0, {0, 0, 187, 282}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(newId, Position{pos.x + size.x, pos.y + sizeyDiff, 0});
        componentManager.getComponent(typeid(Velocity)).emplaceData(newId, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
        componentManager.getComponent(typeid(Enemy)).emplaceData(newId, Enemy{true});
        componentManager.getComponent(typeid(Pattern)).emplaceData(newId, Pattern{TypePattern::DEVOUREROSC, 0});
        componentManager.getComponent(typeid(Size)).emplaceData(newId, Size{(187 * 0.5f) / screenSize->x * windowsSize.x, (282 * 0.5f) / screenSize->y * windowsSize.y});
        componentManager.getComponent(typeid(GroupEntity)).emplaceData(newId, GroupEntity{0, 10, i + 1, 11, {pos.x + size.x, pos.y + sizeyDiff}});
        componentManager.getComponent(typeid(Parent)).emplaceData(newId, Parent{lastId});
        lastId = newId;
        sizeyDiff = 0;
    }
    Position &pos = componentManager.getSingleComponent<Position>(lastId);
    std::size_t newId = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::GROUPEN | InfoComp::PARENT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(newId, SpriteID{18, Priority::LOW});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(newId, SpriteAttribut{0, {0, 0, 237, 256}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(newId, Position{pos.x + 187 * 0.5f, pos.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(newId, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(newId, Enemy{true});
    componentManager.getComponent(typeid(Pattern)).emplaceData(newId, Pattern{TypePattern::DEVOUREROSC, 0});
    componentManager.getComponent(typeid(Size)).emplaceData(newId, Size{(237 * 0.5f) / screenSize->x * windowsSize.x, (256 * 0.5f) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(GroupEntity)).emplaceData(newId, GroupEntity{0, 10, 11, 11, {pos.x + 187 * 0.5f, pos.y}});
    componentManager.getComponent(typeid(Parent)).emplaceData(newId, Parent{lastId});
}
