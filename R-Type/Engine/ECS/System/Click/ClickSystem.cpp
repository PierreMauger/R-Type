#include "Engine/ECS/System/Click/ClickSystem.hpp"

using namespace eng;

ClickSystem::ClickSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize)
{
    this->_window = window;
    this->_screenSize = screenSize;
}

void ClickSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t button = (InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT | InfoComp::SIZE);
    sf::Vector2u windowsSize = this->_window->getSize();

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & button) == button) {
            Button button = componentManager.getSingleComponent<Button>(i);
            Position pos = componentManager.getSingleComponent<Position>(i);
            SpriteAttribut spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*this->_window);

                if (mousePos.x >= pos.x && mousePos.x <= pos.x + spriteAt.rect.width &&
                    mousePos.y >= pos.y && mousePos.y <= pos.y + spriteAt.rect.height) {
                    if (button.type == ButtonType::PLAY) {
                        std::cout << "Play" << std::endl;
                    } else if (button.type == ButtonType::QUIT) {
                        std::cout << "Quit" << std::endl;
                    }
                }
            }
        }
    }
}
