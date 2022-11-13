#include "Engine/ECS/PreloadEntities/BossPreload.hpp"

using namespace eng;

void BossPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::shared_ptr<std::size_t> syncId, sf::Vector2f position)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    std::size_t randBonus = createRandom(0, 4);
    sf::Vector2f size{2 / screenSize->x * windowsSize.x, 2 / screenSize->y * windowsSize.y};
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::APP | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::DROP | InfoComp::SYNCID | InfoComp::SPRITEAT | InfoComp::COOLDOWNSHOOT), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_MINIBOSS, Priority::LOW, 0, 4, false, false, 0, 0.2, 96, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 96, 96}, sf::Color::White, {size.x, size.y}});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, position.y / screenSize->y * windowsSize.y, (position.x - graphic.getScreenSize()->x) / screenSize->x * windowsSize.x});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{(position.x - (250 / screenSize->x * windowsSize.x)) / screenSize->x * windowsSize.x, -192 / screenSize->y * windowsSize.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{3 / screenSize->x * windowsSize.x, size.x, 0, size.y, size.x});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern::CIRCLE, TypeStatus::MOVE, TypePhase::PHASE01, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{96 * size.x, 96 * size.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{1});
    componentManager.getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{randBonus});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 0.5});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{*syncId});
    *syncId += 1;

    std::size_t idBar = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::LIFEBAR | InfoComp::SYNCID), componentManager);
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{0, 0, 0});
    componentManager.getComponent(typeid(LifeBar)).emplaceData(idBar, LifeBar{true, 1});
    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{S_IDBAR, Priority::MEDIUM});
    componentManager.getComponent(typeid(SyncID)).emplaceData(idBar, SyncID{*syncId});
    *syncId += 1;
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{componentManager.getSingleComponent<SyncID>(id).id});
}
