#include "Engine/ECS/System/Score/ScoreSystem.hpp"

using namespace eng;

ScoreSystem::ScoreSystem(std::shared_ptr<sf::RenderWindow> _window, std::shared_ptr<std::vector<sf::Sprite>> _sprites)
{
    this->_window = _window;
    this->_sprites = _sprites;
    this->_death = 0;
    this->_lastSaveScore = 0;
    this->_firstTime = true;
}

void ScoreSystem::createText(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::TEXT), componentManager);

    if (!this->_font.loadFromFile("R-Type/Assets/Fonts/PeachDays.ttf"))
        throw std::runtime_error("Error: Cannot load font");
    this->_text.push_back(sf::Text("Death = 0", this->_font, 20));
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(this->_window->getSize().x) - 50, 10, 0});
    this->_text[0].setPosition(static_cast<float>(this->_window->getSize().x) - 100, 10);
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{sf::Text(this->_text[0]), "death"});
    id = entityManager.addMask((InfoComp::POS | InfoComp::TEXT), componentManager);
    this->_text.push_back(sf::Text("Score = 0", this->_font, 20));
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{static_cast<float>(this->_window->getSize().x) - 50, 50, 0});
    this->_text[1].setPosition(static_cast<float>(this->_window->getSize().x) - 100, 50);
    componentManager.getComponent(typeid(Text)).emplaceData(id, Text{sf::Text(this->_text[1]), "score"});
}

void ScoreSystem::createVessel(ComponentManager &componentManager, EntityManager &entityManager, std::shared_ptr<std::vector<sf::Sprite>> sprites,
                               std::shared_ptr<sf::RenderWindow> window)
{
    std::size_t id = entityManager.addMask(
        (InfoComp::POS | InfoComp::LIFE | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::CONTROLLABLE | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE | InfoComp::APP),
        componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{6, Priority::MEDIUM, 0, 0, 0, 0, 0, 64, 0});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{10, -200, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{0, 0, 0, 5});
    componentManager.getComponent(typeid(Appearance)).emplaceData(id, Appearance{true, 100});
    componentManager.getComponent(typeid(Controllable)).emplaceData(id, Controllable{true, this->_lastSaveScore});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, 1, 1});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{64, 28});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{1});
    sprites->at(6).setTextureRect(sf::IntRect(0, 0, 64, 28));
    this->_lastSaveScore = 0;

    std::size_t idBar = entityManager.addMask((InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARENT | InfoComp::COOLDOWNBAR), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(idBar, SpriteID{1, Priority::HIGH});
    componentManager.getComponent(typeid(Position)).emplaceData(idBar, Position{10, static_cast<float>(window->getSize().y) - 20, 0});
    componentManager.getComponent(typeid(Parent)).emplaceData(idBar, Parent{id});
    componentManager.getComponent(typeid(CooldownBar)).emplaceData(idBar, CooldownBar{true});
}

bool ScoreSystem::findVessel(ComponentManager &componentManager, EntityManager &entityManager, Controllable &controllable)
{
    auto &masks = entityManager.getMasks();
    std::size_t checkCon = (InfoComp::CONTROLLABLE);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & checkCon) == checkCon) {
            controllable = componentManager.getSingleComponent<Controllable>(i);
            this->_lastSaveScore = controllable.kill;
            return true;
        }
    }
    return false;
}

void ScoreSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t checkText = (InfoComp::TEXT);
    Controllable controllable;

    if (this->_firstTime) {
        createText(componentManager, entityManager);
        this->_firstTime = false;
    }
    if (!findVessel(componentManager, entityManager, controllable)) {
        createVessel(componentManager, entityManager, this->_sprites, this->_window);
        this->_death++;
    }
    for (std::size_t i = 0; i < masks.size(); i++) {
        if (!masks[i].has_value())
            continue;
        if ((masks[i].value() & checkText) == checkText) {
            Text &txt = componentManager.getSingleComponent<Text>(i);
            if (txt.str == "death" && txt.text.getString() != "Death: " + std::to_string(this->_death))
                txt.text.setString("Death: " + std::to_string(this->_death));
            if (txt.str == "score" && txt.text.getString() != "Score: " + std::to_string(controllable.kill))
                txt.text.setString("Score: " + std::to_string(controllable.kill));
        }
    }
}