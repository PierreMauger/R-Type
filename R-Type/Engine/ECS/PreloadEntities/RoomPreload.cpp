#include "Engine/ECS/PreloadEntities/RoomPreload.hpp"

using namespace eng;

void RoomPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t mask = (InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT | InfoComp::TEXT | InfoComp::SIZE | InfoComp::SCENE);
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    std::size_t id = 0;
    float textSize = 30.0f / screenSize->x * windowsSize.x;

    id = entityManager.addMask(mask, componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_BUTTON, Priority::MEDIUM});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 265, 116}, sf::Color::White, {1 / screenSize->x * windowsSize.x, 1 / screenSize->y * windowsSize.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(windowsSize.x / 2 - (265 / screenSize->x * windowsSize.x) / 2), static_cast<float>(windowsSize.y * 2 / 3 - (116 / screenSize->y * windowsSize.y) / 2), 0});
    componentManager.getComponent(typeid(Button)).emplaceData(id, Button{ButtonType::READY});
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{"Start", false, 0, textSize, sf::Color::White, {static_cast<float>(windowsSize.x / 2), static_cast<float>(windowsSize.y * 2 / 3)}});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{265 / screenSize->x * windowsSize.x, 116 / screenSize->y * windowsSize.y});
    componentManager.getComponent(typeid(Scene)).emplaceData(id, Scene{SceneType::ROOM});
}
