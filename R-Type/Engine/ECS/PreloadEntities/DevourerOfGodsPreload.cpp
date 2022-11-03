#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"

using namespace eng;

void DevourerPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    std::size_t lastId = 0;
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{16, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 375, 311}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x + 80), static_cast<float>(windowsSize.y) / 2, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern::BIGOSCILLATION, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{(375 * 0.5f) / screenSize->x * windowsSize.x, (331 * 0.5f) / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});

    for (std::size_t i = 0; i < 10; i++) {
        lastId = id;
        Position &pos = componentManager.getSingleComponent<Position>(lastId);
        id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::SPRITEAT | InfoComp::PARENT), componentManager);
        componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{15, Priority::MEDIUM});
        componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 187, 282}, sf::Color::White, {0.5f / screenSize->x * windowsSize.x, 0.5f / screenSize->y * windowsSize.y}});
        componentManager.getComponent(typeid(Position)).emplaceData(id, Position{pos.x + 187, pos.y, 0});
        componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
        componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
        componentManager.getComponent(typeid(Size)).emplaceData(id, Size{(187 * 0.5f) / screenSize->x * windowsSize.x, (282 * 0.5f) / screenSize->y * windowsSize.y});
        componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});
        componentManager.getComponent(typeid(Parent)).emplaceData(id, Parent{lastId, true});
    }
}
