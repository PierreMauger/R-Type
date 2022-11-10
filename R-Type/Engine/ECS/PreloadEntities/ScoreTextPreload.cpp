#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"

using namespace eng;

void ScoreTextPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();

    std::size_t idScore = entityManager.addMask((InfoComp::TEXT), componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(idScore, Text{"Score: ", true, 0, {static_cast<float>(graphic.getWindow()->getSize().x - (150 / screenSize->x * windowsSize.x)), 10}});

    std::size_t idKill = entityManager.addMask((InfoComp::TEXT), componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(idKill, Text{"Death: ", true, 0, {static_cast<float>(graphic.getWindow()->getSize().x - (150 / screenSize->x * windowsSize.x)), 50}});
}

void ScoreTextPreload::levelPreload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();

    std::size_t idScore = entityManager.addMask((InfoComp::TEXT), componentManager);
    componentManager.getComponent(typeid(Text)).emplaceData(idScore, Text{"Level Done !", true, 0, {static_cast<float>(graphic.getWindow()->getSize().x / 2), static_cast<float>(graphic.getWindow()->getSize().y / 2)}});
}