#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"

using namespace eng;

void DevourerPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f position)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    std::size_t lastId = 0;
    float randY = createRandom(200 / screenSize->y * windowsSize.y, windowsSize.y - (100 / screenSize->y * windowsSize.y));
    float scal = 0.5f;

    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::SPRITEAT | InfoComp::CHAIN), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_DEVOURER_TAIL, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 237, 256}, sf::Color::White, {scal / screenSize->x * windowsSize.x, scal / screenSize->y * windowsSize.y}, {237 / 2, 256 / 2}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{position.x / screenSize->x * windowsSize.x, position.y / screenSize->y * windowsSize.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{(237 / screenSize->x * windowsSize.x) * scal, (256 / screenSize->y * windowsSize.y) * scal});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});
    componentManager.getComponent(typeid(Chain)).emplaceData(id, Chain{S_DEVOURER_TAIL, 0, (237 / 2), (256 / 2)});
    lastId = id;

    Position pos = componentManager.getSingleComponent<Position>(id);

    for (size_t cpt = 0; cpt < 10; cpt++, lastId = id) {
        id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::SPRITEAT | InfoComp::CHAIN), componentManager);
        componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_DEVOURER_BODY, Priority::MEDIUM});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 187, 282}, sf::Color::White, {scal / screenSize->x * windowsSize.x, scal / screenSize->y * windowsSize.y}, {187 / 2, 282 / 2}});
        componentManager.getComponent(typeid(Position)).emplaceData(id, Position{pos.x, pos.y, 0});
        componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0});
        componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
        componentManager.getComponent(typeid(Size)).emplaceData(id, Size{(187 / screenSize->x * windowsSize.x) * scal, (282 / screenSize->y * windowsSize.y) * scal});
        componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});
        componentManager.getComponent(typeid(Chain)).emplaceData(id, Chain{S_DEVOURER_BODY, lastId, (187 / 2), (282 / 2)});
    }

    id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::SYNCID | InfoComp::PATTERN | InfoComp::DROP | InfoComp::SPRITEAT | InfoComp::CHAIN), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_DEVOURER_HEAD, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 375, 331}, sf::Color::White, {scal / screenSize->x * windowsSize.x, scal / screenSize->y * windowsSize.y}, {375 / 2, 331 / 2}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{pos.x, pos.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern::DEVOUREROSC, TypeStatus(SEARCH), TypePhase(PHASE01), 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{(375 / screenSize->x * windowsSize.x) * scal, (331 / screenSize->y * windowsSize.y) * scal});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});
    componentManager.getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{static_cast<std::size_t>(randY) % 2});
    componentManager.getComponent(typeid(Chain)).emplaceData(id, Chain{S_DEVOURER_HEAD, lastId, (375 / 2), (331 / 2)});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{syncId++});
}
