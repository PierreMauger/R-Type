#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"

void eng::ParallaxPreload::preload(Engine &engine)
{
    std::size_t id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT),
                                                                engine.getECS().getComponentManager());
    float x = engine.getGraphic().getWindow()->getSize().x;
    float y = engine.getGraphic().getWindow()->getSize().y;
    ComponentManager &componentManager = engine.getECS().getComponentManager();

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{10, Priority::HIGH});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::IntRect(0, 0, 800, 600), sf::Color::White, sf::Vector2f(x / 800, y / 600)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{14, Priority::HIGH});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::IntRect(0, 0, 800, 600), sf::Color::White, sf::Vector2f(x / 800, y / 600)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.6, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::IntRect(0, 0, 800, 600), sf::Color::White, sf::Vector2f(x / 800, y / 600)});
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{11, Priority::HIGH});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{13, Priority::HIGH});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::IntRect(0, 0, 800, 600), sf::Color::White, sf::Vector2f(x / 800, y / 600)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 250, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1.5, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = engine.getECS().getEntityManager().addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{12, Priority::HIGH});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::IntRect(0, 0, 800, 600), sf::Color::White, sf::Vector2f(x / 800, y / 600)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
}
