#include "Engine/ECS/PreloadEntities/MenuPreload.hpp"

using namespace eng;

void MenuPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t mask = (InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT | InfoComp::TEXT | InfoComp::SIZE);
    std::size_t id = entityManager.addMask(mask, componentManager);
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_BUTTON, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 265, 116}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x / 2 - 265 / 2), static_cast<float>(windowsSize.y * 2 / 3 - 116 / 2), 0});
    componentManager.getComponent(typeid(Button)).emplaceData(id, Button{ButtonType::QUIT});
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{"Quit", false, 0, {static_cast<float>(windowsSize.x / 2), static_cast<float>(windowsSize.y * 2 / 3)}});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{265, 116});

    id = entityManager.addMask(mask, componentManager);
    std::size_t idIp = id;
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_BUTTON, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 265, 116}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x / 3 - 265 / 2), static_cast<float>(windowsSize.y / 2 - 116 / 2), 0});
    componentManager.getComponent(typeid(Button)).emplaceData(id, Button{ButtonType::TEXTZONE, false, 15});
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{"", false, 0, {static_cast<float>(windowsSize.x / 3), static_cast<float>(windowsSize.y / 2)}});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{265, 116});

    id = entityManager.addMask(InfoComp::TEXT, componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{"IP", false, 0, {static_cast<float>(windowsSize.x / 3), static_cast<float>(windowsSize.y / 2 - 116 / 2)}});

    id = entityManager.addMask(mask, componentManager);
    std::size_t idPort = id;
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_BUTTON, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 265, 116}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x / 3 - 265 / 2), static_cast<float>(windowsSize.y / 3 - 116 / 2), 0});
    componentManager.getComponent(typeid(Button)).emplaceData(id, Button{ButtonType::TEXTZONE, false, 4});
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{"", false, 0, {static_cast<float>(windowsSize.x / 3), static_cast<float>(windowsSize.y / 3)}});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{265, 116});

    id = entityManager.addMask(InfoComp::TEXT, componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{"PORT", false, 0, {static_cast<float>(windowsSize.x / 3), static_cast<float>(windowsSize.y / 3 - 116 / 2)}});

    id = entityManager.addMask((mask | InfoComp::PARENT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_BUTTON, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 265, 116}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x * 2 / 3 - 265 / 2), static_cast<float>(windowsSize.y * 2 / 5 - 116 / 2), 0});
    componentManager.getComponent(typeid(Button)).emplaceData(id, Button{ButtonType::CONNECT});
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{"Connect", false, 0, {static_cast<float>(windowsSize.x * 2 / 3), static_cast<float>(windowsSize.y * 2 / 5)}});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{265, 116});
    componentManager.getComponent(typeid(Parent)).emplaceData(id, Parent{idIp, idPort});
}
