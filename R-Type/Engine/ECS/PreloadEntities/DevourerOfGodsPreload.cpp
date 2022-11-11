#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"

using namespace eng;

void DevourerPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t &syncId, sf::Vector2f position)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    std::size_t lastId = 0;
    sf::Vector2f size{0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y};
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SYNCID | InfoComp::SPRITEAT), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_DEVOURER_HEAD, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 375, 311}, sf::Color::White, {size.x, size.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{position.x / screenSize->x * windowsSize.x, position.y / screenSize->y * windowsSize.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{3 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern::BIGOSCILLATION, TypeStatus(IDLE), TypePhase(PHASE01), 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{375 * size.x, 375 * size.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{syncId++});

    for (std::size_t i = 0; i < 10; i++) {
        lastId = id;
        Position &pos = componentManager.getSingleComponent<Position>(lastId);
        id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::SPRITEAT | InfoComp::PARENT), componentManager);
        componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_2, Priority::MEDIUM});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 187, 282}, sf::Color::White, {size.x, size.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(id, Position{pos.x + 187, pos.y, 0});
        componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
        componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
        componentManager.getComponent(typeid(Size)).emplaceData(id, Size{187 * size.x, 282 * size.y});
        componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});
        componentManager.getComponent(typeid(Parent)).emplaceData(id, Parent{lastId, true});
    }
}
