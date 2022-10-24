#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"

using namespace eng;

void EnemyPreload::preload(Engine &engine)
{
    std::size_t rand = static_cast<std::size_t>(createRandom(0, 3));
    float randY = createRandom(150, 450);
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATERN | InfoComp::SPRITEAT),
        engine.getECS().getComponentManager());
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{2, Priority::MEDIUM, 0, 2, false, 0, 0.075, 63, 0});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 63, 48}, sf::Color::White, {
        1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x + 80), randY, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern(rand), 0});
    engine.getECS().getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true, 0, (float)(rand == 0 ? 1.0 : 0.0)});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{63 / screenSize->x * windowsSize.x, 48 / screenSize->y * windowsSize.y});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{2});
}
