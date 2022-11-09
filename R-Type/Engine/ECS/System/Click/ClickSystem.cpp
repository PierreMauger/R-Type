#include "Engine/ECS/System/Click/ClickSystem.hpp"

using namespace eng;

ClickSystem::ClickSystem(Graphic &graphic, std::shared_ptr<std::size_t> port, std::shared_ptr<std::string> ip, EntityManager &entityManager)
{
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
    this->_event = graphic.getEvent();
    this->_sceneId = graphic.getSceneId();

    this->_port = port;
    this->_ip = ip;

    entityManager.addMaskCategory(this->_buttonTag);
}

void ClickSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    unsigned long int changed = -1;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (auto id : entityManager.getMaskCategory(this->_buttonTag)) {
            Button &button = componentManager.getSingleComponent<Button>(id);
            Position pos = componentManager.getSingleComponent<Position>(id);
            Size size = componentManager.getSingleComponent<Size>(id);

            if (entityManager.hasMask(id, this->_sceneTag)) {
                Scene &scene = componentManager.getSingleComponent<Scene>(id);
                if (scene.id != *this->_sceneId)
                    continue;
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->_window);

            if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x && mousePos.y >= pos.y && mousePos.y <= pos.y + size.y) {
                if (button.type == ButtonType::PLAY_SOLO) {
                    *this->_sceneId = *this->_sceneId + 1;
                } else if (button.type == ButtonType::QUIT) {
                    this->_window->close();
                } else if (button.type == ButtonType::TEXTZONE) {
                    button.selected = true;
                    changed = id;
                } else if (button.type == ButtonType::CONNECT) {
                    if (*this->_sceneId != 0)
                        continue;
                    Parent parent = componentManager.getSingleComponent<Parent>(id);
                    std::string text = componentManager.getSingleComponent<Text>(parent.id).str;
                    std::string text2 = componentManager.getSingleComponent<Text>(parent.id2).str;
                    *this->_sceneId = *this->_sceneId + 1;
                    *this->_ip = text;
                    text2 != "" ? *this->_port = std::stoi(text2) : *this->_port = 0;
                }
            }
            if (changed) {
                for (auto id : entityManager.getMaskCategory(this->_buttonTag)) {
                    Button &button = componentManager.getSingleComponent<Button>(id);
                    if (button.type == ButtonType::TEXTZONE && id != changed)
                        button.selected = false;
                }
            }
        }
    }
}
