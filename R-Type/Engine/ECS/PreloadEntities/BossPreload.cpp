#include "Engine/ECS/PreloadEntities/BossPreload.hpp"

using namespace eng;

void BossPreload::preload(Engine &engine)
{
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();
    float randY = createRandom(180 / screenSize->y * windowsSize.y, 420 / screenSize->y * windowsSize.y);
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::VEL | InfoComp::APP | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE |
                                                                 InfoComp::SIZE | InfoComp::PATERN | InfoComp::DROP | InfoComp::SPRITEAT | InfoComp::COOLDOWNSHOOT),
                                                                engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{5, Priority::MEDIUM, 0, 4, false, false, 0, 0.2, 96, 0});
    engine.getECS()
        .getComponentManager()
        .getComponent(typeid(SpriteAttribut))
        .emplaceData(id, SpriteAttribut{0, {0, 0, 96, 96}, sf::Color::White, {2 / screenSize->x * windowsSize.x, 2 / screenSize->y * windowsSize.y}});
    engine.getECS().getComponentManager().getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, randY});
    engine.getECS()
        .getComponentManager()
        .getComponent(typeid(Position))
        .emplaceData(id,
                     Position{static_cast<float>(engine.getGraphic().getWindow()->getSize().x - (300 / screenSize->x * windowsSize.x)), -96 / screenSize->y * windowsSize.y, 0});
    engine.getECS()
        .getComponentManager()
        .getComponent(typeid(Velocity))
        .emplaceData(id, Velocity{0, -2 / screenSize->y * windowsSize.y * -1, 0, 2 / screenSize->x * windowsSize.x, 2 / screenSize->y * windowsSize.y});
    engine.getECS().getComponentManager().getComponent(typeid(Patern)).emplaceData(id, Patern{TypePatern::CIRCLE, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{96 * 2 / screenSize->x * windowsSize.x, 96 * 2 / screenSize->y * windowsSize.y});
    engine.getECS().getComponentManager().getComponent(typeid(Life)).emplaceData(id, Life{10});
    engine.getECS().getComponentManager().getComponent(typeid(DropBonus)).emplaceData(id, DropBonus{1});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 0.5});

    std::size_t idBar = engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::LIFEBAR), engine.getECS().getComponentManager());
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(idBar, Position{0, 0, 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    engine.getECS().getComponentManager().getComponent(typeid(LifeBar)).emplaceData(idBar, LifeBar{true, 10});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::MEDIUM});
}
