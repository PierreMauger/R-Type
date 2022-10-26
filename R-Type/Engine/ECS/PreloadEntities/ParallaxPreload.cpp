#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"

void eng::ParallaxPreload::preload(Engine &engine)
{
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT),
                                                                engine.getECS().getComponentManager());
    ComponentManager &componentManager = engine.getECS().getComponentManager();
    sf::Vector2u windowsSize = engine.getGraphic().getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = engine.getGraphic().getScreenSize();

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{10, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{13, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1.5, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{14, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.6, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 96, 96), sf::Color::White, sf::Vector2f(2 / screenSize->x * windowsSize.x, 2 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{11, Priority::HIGH, 0, 76, true, false, 0, 0.025, 96, 0});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{12, Priority::HIGH});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 96, 96), sf::Color::White, sf::Vector2f(3 / screenSize->x * windowsSize.x, 3 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 500 / screenSize->y * windowsSize.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
}
