#include "Engine/ECS/PreloadEntities/CooldownBarPreload.hpp"

void eng::CooldownBarPreload::preload(Engine &engine)
{
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();
    std::size_t id =
        engine.getECS().getEntityManager().addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), engine.getECS().getComponentManager());

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_IDBAR, Priority::LOW});
    engine.getECS()
        .getComponentManager()
        .getComponent(typeid(Position))
        .emplaceData(id, Position{10, (float)engine.getGraphic().getWindow()->getSize().y - (20 / screenSize->y * windowsSize.y), 0});
    engine.getECS().getComponentManager().getComponent(typeid(Parent)).emplaceData(id, Parent{5});
    engine.getECS().getComponentManager().getComponent(typeid(CooldownBar)).emplaceData(id, CooldownBar{true});
}
