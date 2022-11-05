#include "Engine/ECS/System/Click/ClickSystem.hpp"

using namespace eng;

ClickSystem::ClickSystem(Graphic &graphic, EntityManager &entityManager)
{
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();

    entityManager.addMaskCategory(this->_buttonTag);
}

void ClickSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    unsigned long int changed = -1;

    for (auto id : entityManager.getMaskCategory(this->_buttonTag)) {
        Button &button = componentManager.getSingleComponent<Button>(id);
        Position pos = componentManager.getSingleComponent<Position>(id);
        SpriteAttribut spriteAt = componentManager.getSingleComponent<SpriteAttribut>(id);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->_window);

            if (mousePos.x >= pos.x && mousePos.x <= pos.x + spriteAt.rect.width && mousePos.y >= pos.y && mousePos.y <= pos.y + spriteAt.rect.height) {
                if (button.type == ButtonType::PLAY) {
                    componentManager.clear();
                    entityManager.clear();
                    ParallaxPreload::preload(this->_window, this->_screenSize, entityManager, componentManager);
                } else if (button.type == ButtonType::QUIT) {
                    this->_window->close();
                } else if (button.type == ButtonType::TEXTZONE) {
                    button.selected = true;
                    changed = id;
                }
            }
            if (changed) {
                for (auto id : entityManager.getMaskCategory(this->_buttonTag)) {
                    Button &button = componentManager.getSingleComponent<Button>(id);
                    if (button.type == ButtonType::TEXTZONE && id != changed) {
                        button.selected = false;
                    }
                }
            }
        }
    }
}
