#include "Engine/ECS/PreloadEntities/MenuPreload.hpp"

using namespace eng;

void MenuPreload::preload(Engine &engine)
{
    std::size_t mask = (InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT | InfoComp::TEXT | InfoComp::SIZE);
    std::size_t id = engine.getECS().getEntityManager().addMask(mask, engine.getECS().getComponentManager());
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();

    engine.getECS().getComponentManager().getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{10, Priority::MEDIUM});
    engine.getECS().getComponentManager().getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 265, 116}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    engine.getECS().getComponentManager().getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x / 2 - 265 / 2), static_cast<float>(windowsSize.y / 2 - 116 / 2), 0});
    engine.getECS().getComponentManager().getComponent(typeid(Button)).emplaceData(id, Button{ButtonType::QUIT});
    engine.getECS().getComponentManager().getComponent(typeid(Text)).emplaceData(id, Text{"Quit", false, 0, {static_cast<float>(windowsSize.x / 2), static_cast<float>(windowsSize.y / 2)}});
    engine.getECS().getComponentManager().getComponent(typeid(Size)).emplaceData(id, Size{265, 116});
}
