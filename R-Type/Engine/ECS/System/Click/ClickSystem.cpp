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
    std::size_t button = (InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & button) == button) {
            Button button = componentManager.getSingleComponent<Button>(i);
            Position pos = componentManager.getSingleComponent<Position>(i);
            SpriteID spriteId = componentManager.getSingleComponent<SpriteID>(i);
            SpriteAttribut spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (sf::Mouse::getPosition(*this->_window).x > pos.x && sf::Mouse::getPosition(*this->_window).x < pos.x + spriteAt.rect.width * spriteAt.scale.x && sf::Mouse::getPosition(*this->_window).y > pos.y && sf::Mouse::getPosition(*this->_window).y < pos.y + spriteAt.rect.height * spriteAt.scale.y)
                    std::cout << "Quit" << std::endl;
            }
        }
    }
}
