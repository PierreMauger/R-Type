#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"

void eng::EnemyPreload::preload(Engine &engine)
{
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();
    std::size_t rand = static_cast<std::size_t>(createRandom(0, 3));
    float randY = createRandom(150 / screenSize->y * windowsSize.y, 450 / screenSize->y * windowsSize.y);
    std::size_t id = engine.getECS().getEntityManager().addMask(
        (InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SPRITEAT | InfoComp::COOLDOWNSHOOT),
        engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{2, Priority::MEDIUM, 0, 2, false, false, 0, 0.075, 63, 0});
    engine.getECS()
        .getComponentManager()
        .getComponent(typeid(SpriteAttribut))
        .emplaceData(id, SpriteAttribut{0, {0, 0, 63, 48}, sf::Color::White, {2 / screenSize->x * windowsSize.x, 2 / screenSize->y * windowsSize.y}});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x + 80 / screenSize->x * windowsSize.x), randY, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Velocity)).emplaceData(id, Velocity{2 / screenSize->x * windowsSize.x * -1, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern(rand), 0});
    engine.getECS().getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{63 * 2 / screenSize->x * windowsSize.x, 48 * 2 / screenSize->y * windowsSize.y});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{2});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, (float)(rand == 0 ? 1.0 : 0.0)});
}
