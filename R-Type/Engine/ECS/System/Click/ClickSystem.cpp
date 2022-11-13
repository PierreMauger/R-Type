#include "Engine/ECS/System/Click/ClickSystem.hpp"

using namespace eng;

ClickSystem::ClickSystem(Graphic &graphic, EntityManager &entityManager)
{
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
    this->_event = graphic.getEvent();

    this->_sceneId = graphic.getSceneId();
    this->_port = graphic.getPort();
    this->_ip = graphic.getIp();
    this->_isLocal = graphic.getIsLocal();
    this->_isReady = graphic.getIsReady();
    this->_syncId = graphic.getSyncId();
    this->_roomPlayerNb = graphic.getRoomPlayerNb();
    this->_roomPlayerMax = graphic.getRoomPlayerMax();

    entityManager.addMaskCategory(this->_buttonTag);
}

void ClickSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    unsigned long int changed = -1;
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->_window);

    for (auto id : entityManager.getMaskCategory(this->_buttonTag)) {
        Button &button = componentManager.getSingleComponent<Button>(id);
        Position pos = componentManager.getSingleComponent<Position>(id);
        Size size = componentManager.getSingleComponent<Size>(id);
        SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(id);

        if (entityManager.hasMask(id, this->_sceneTag)) {
            Scene scene = componentManager.getSingleComponent<Scene>(id);
            if (scene.id != *this->_sceneId)
                continue;
        }
        if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x && mousePos.y >= pos.y && mousePos.y <= pos.y + size.y) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                spriteAt.color = sf::Color(128, 128, 128, 255);
                changed = id;
            }
            if (this->_event->type == sf::Event::MouseButtonReleased && this->_event->mouseButton.button == sf::Mouse::Left) {
                if (button.type == ButtonType::PLAY_SOLO) {
                    *this->_sceneId = SceneType::GAME;
                    *this->_isLocal = true;
                    VesselPreload::preload(this->_window->getSize(), this->_screenSize, entityManager, componentManager, this->_syncId, *this->_syncId % 4);
                } else if (button.type == ButtonType::QUIT) {
                    this->_window->close();
                } else if (button.type == ButtonType::READY) {
                    *this->_isReady = true;
                } else if (button.type == ButtonType::TEXTZONE) {
                    button.selected = true;
                } else if (button.type == ButtonType::CONNECT) {
                    Parent parent = componentManager.getSingleComponent<Parent>(id);
                    std::string text = componentManager.getSingleComponent<Text>(parent.id).str;
                    std::string text2 = componentManager.getSingleComponent<Text>(parent.id2).str;
                    *this->_ip = text;
                    text2 != "" ? *this->_port = std::stoi(text2) : *this->_port = 0;
                } else if (button.type == ButtonType::CREATE_ROOM) {
                    Parent parent = componentManager.getSingleComponent<Parent>(id);
                    std::string text = componentManager.getSingleComponent<Text>(parent.id).str;
                    text != "" ? *this->_roomPlayerMax = std::stoi(text) : *this->_roomPlayerMax = 4;
                }
            }
        }
    }
    for (auto id : entityManager.getMaskCategory(this->_buttonTag)) {
        Button &button = componentManager.getSingleComponent<Button>(id);
        SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(id);
        Position pos = componentManager.getSingleComponent<Position>(id);
        Size size = componentManager.getSingleComponent<Size>(id);

        if (id != changed) {
            if (button.type == ButtonType::TEXTZONE && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                button.selected = false;
            if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x && mousePos.y >= pos.y && mousePos.y <= pos.y + size.y)
                spriteAt.color = sf::Color(200, 200, 200, 255);
            else
                spriteAt.color = sf::Color::White;
        }
    }
}
