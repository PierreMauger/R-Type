#include "Engine/ECS/PreloadEntities/ObstaclePreload.hpp"

using namespace eng;

void ObstaclePreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::shared_ptr<std::size_t> syncId, sf::Vector2f pos)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::SIZE | InfoComp::SYNCID | InfoComp::SPRITEAT | InfoComp::ENEMY), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_3, Priority::MEDIUM});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{pos.x / screenSize->x * windowsSize.x, pos.y / screenSize->y * windowsSize.y, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 38, 33), sf::Color::White, sf::Vector2f(3 / screenSize->x * windowsSize.x, 3 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{(3 / screenSize->x * windowsSize.x) * -1, 0, 0});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{114 / screenSize->x * windowsSize.x, 99 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{*syncId});
    *syncId += 1;
}
