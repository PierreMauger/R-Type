#include "Engine/ECS/System/Click/ClickSystem.hpp"

using namespace eng;

ClickSystem::ClickSystem(Graphic &graphic, EntityManager &entityManager)
{
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();

    entityManager.addMaskCategory(InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT | InfoComp::SIZE);
}

void ClickSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t button = (InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT | InfoComp::SIZE);

    for (auto id : entityManager.getMaskCategory(button)) {
        Button button = componentManager.getSingleComponent<Button>(id);
        Position pos = componentManager.getSingleComponent<Position>(id);
        SpriteAttribut spriteAt = componentManager.getSingleComponent<SpriteAttribut>(id);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->_window);

            if (mousePos.x >= pos.x && mousePos.x <= pos.x + spriteAt.rect.width && mousePos.y >= pos.y && mousePos.y <= pos.y + spriteAt.rect.height) {
                if (button.type == ButtonType::PLAY) {
                    componentManager.clear();
                    entityManager.clear();
                    // ParallaxPreload::preload(componentManager, entityManager, this->_window, this->_screenSize);
                } else if (button.type == ButtonType::QUIT) {
                    this->_window->close();
                }
            }
        }
    }
}
