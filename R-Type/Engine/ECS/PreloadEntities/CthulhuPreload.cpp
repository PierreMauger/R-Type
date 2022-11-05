#include "Engine/ECS/PreloadEntities/CthulhuPreload.hpp"

using namespace eng;

void CthulhuPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    float randY = createRandom(200 / screenSize->y * windowsSize.y, windowsSize.y - (100 / screenSize->y * windowsSize.y));
    sf::Vector2f size{screenSize->x / (1920 / 2), screenSize->y / (1080 / 2)};
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::APP | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::DROP | InfoComp::SPRITEAT | InfoComp::COOLDOWNSHOOT), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{19, Priority::MEDIUM, 0, 2, false, false, 0, 0.2, 110, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 110, 162}, sf::Color::White, {size.x / screenSize->x * windowsSize.x, size.y / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, randY});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x - (300 / screenSize->x * windowsSize.x)), -96 / screenSize->y * windowsSize.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, size.x / screenSize->y * windowsSize.y, 0, size.y / screenSize->x * windowsSize.x, size.x / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern::CTHULHU, TypeStatus(SEARCH), TypePhase(PHASE01), 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{96 * size.x / screenSize->x * windowsSize.x, 96 * size.y / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});
    componentManager.getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{static_cast<std::size_t>(randY) % 2});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 2});

    std::size_t idBar = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::LIFEBAR), componentManager);
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{0, 0, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    componentManager.getComponent(typeid(LifeBar)).emplaceData(idBar, LifeBar{true, 10});
    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::MEDIUM});
}
