#include "Engine/ECS/System/Score/ScoreSystem.hpp"

using namespace eng;

ScoreSystem::ScoreSystem(std::shared_ptr<sf::RenderWindow> _window, std::shared_ptr<std::vector<sf::Sprite>> _sprites)
{
    this->_window = _window;
    this->_sprites = _sprites;
    this->_death = 0;
    this->_firstTime = true;
}

void ScoreSystem::createText(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::TEXT), componentManager);
    sf::Font font;
    if (!font.loadFromFile("R-Type/Assets/Fonts/GameCube.ttf"))
        throw std::runtime_error("Error: Cannot load font");
    sf::Text text("Score: 0", font, 20);

    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, static_cast<float>(this->_window->getSize().x) - 50, 0});
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{text});
}

void ScoreSystem::createVessel(ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<std::vector<sf::Sprite>> sprites,
                               std::shared_ptr<sf::RenderWindow> window)
{
    std::size_t id = entityManager.addMask(
        (InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP),
        componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, 0, 0, 0, 32, 0});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, -200, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, 5});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    componentManager.getComponent(typeid(Controllable)).emplaceData(id, Controllable{true});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{32, 14});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{1});
    sprites->at(6).setTextureRect(sf::IntRect(0, 0, 32, 14));

    std::size_t idBar = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(window->getSize().y) - 20, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    componentManager.getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}

void ScoreSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t checkCon = (InfoComp::CONTROLLABLE);
    std::size_t checkText = (InfoComp::TEXT);
    bool dead = true;

    if (this->_firstTime) {
        createText(componentManager, entityManager);
        this->_firstTime = false;
    }
    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & checkCon) == checkCon)
            dead = false;
        if ((masks[i].value() & checkText) == checkText)
            componentManager.getSingleComponent<Text>(i).text.setString("Score: " + std::to_string(this->_death));
    }
    if (dead) {
        createVessel(componentManager, entityManager, this->_sprites, this->_window);
        this->_death++;
    }
}