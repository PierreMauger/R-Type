#include "Engine/ECS/PreloadEntities/DevourerOfGodsPreload.hpp"

void eng::DevourerPreload::preload(Engine &engine)
{
    ComponentManager &componentManager = engine.getECS().getComponentManager();
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATERN | InfoComp::SPRITEAT),
        engine.getECS().getComponentManager());

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{15, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut))
        .emplaceData(id, SpriteAttribut{0, {0, 0, 331, 375}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x + 80), static_cast<float>(windowsSize.y) / 2, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    componentManager.getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern::BIGOSCILLATION, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, 0});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{331 / screenSize->x * windowsSize.x, 375 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{10});
}
