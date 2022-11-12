#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"

using namespace eng;

void ScoreTextPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    float sText = 30 / screenSize->x * windowsSize.x;

    std::size_t idScore = entityManager.addMask((InfoComp::TEXT), componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(idScore, Text{"Score: ", true, 0, sText, sf::Color::White, {static_cast<float>(graphic.getWindow()->getSize().x - (150 / screenSize->x * windowsSize.x)), 10 / screenSize->y * windowsSize.y}});

    std::size_t idKill = entityManager.addMask((InfoComp::TEXT), componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(idKill, Text{"Death: ", true, 0, sText, sf::Color::White, {static_cast<float>(graphic.getWindow()->getSize().x - (150 / screenSize->x * windowsSize.x)), 50 / screenSize->y * windowsSize.y}});
}

void ScoreTextPreload::levelPreload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    float sText = 150 / screenSize->x * windowsSize.x;

    std::size_t idScore = entityManager.addMask((InfoComp::TEXT), componentManager);
    componentManager.getComponent(typeid(Text))
        .emplaceData(idScore, Text{"Level Completed !", false, 0, sText, sf::Color::White, {static_cast<float>(graphic.getWindow()->getSize().x / 4), static_cast<float>(graphic.getWindow()->getSize().y / 2.25)}, graphic.getClock()->getElapsedTime().asSeconds(), 2});
}