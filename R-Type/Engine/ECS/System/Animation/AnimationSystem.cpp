#include "Engine/ECS/System/Animation/AnimationSystem.hpp"

using namespace eng;

AnimationSystem::AnimationSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::Sprite>> sprites)
{
    this->_event = event;
    this->_clock = clock;
    this->_sprites = sprites;
}

void AnimationSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t spriteMask = (InfoComp::SPRITEID | InfoComp::SIZE | InfoComp::SPRITEAT);
    std::size_t appMask = (InfoComp::APP);
    std::size_t contMask = (InfoComp::CONTROLLABLE);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & spriteMask) == spriteMask) {
            SpriteID &spriteID = componentManager.getSingleComponent<SpriteID>(i);
            SpriteAttribut &spriteAT = componentManager.getSingleComponent<SpriteAttribut>(i);
            Size &sz = componentManager.getSingleComponent<Size>(i);
            if (masks[i].has_value() && (masks[i].value() & contMask) == contMask) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    spriteAT.rect.left = spriteID.offsetX * 2;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    spriteAT.rect.left = spriteID.offsetX;
                else
                    spriteAT.rect.left = 0;
                continue;
            }
            if (spriteID.nbFrame == 0 || ((masks[i].value() & appMask) == appMask && componentManager.getSingleComponent<Appearance>(i).app))
                continue;
            if (this->_clock->getElapsedTime().asSeconds() >= spriteID.lastTime + spriteID.delay) {
                if (spriteID.curFrame == 0)
                    spriteID.sign = false;
                if (spriteID.curFrame == spriteID.nbFrame)
                    spriteID.sign = true;
                spriteID.sign == false ? spriteID.curFrame++ : spriteID.curFrame--;
                spriteAT.rect.left = spriteID.offsetX * spriteID.curFrame;
                spriteAT.rect.top = spriteID.offsetY * spriteID.curFrame;
                spriteID.lastTime = this->_clock->getElapsedTime().asSeconds();
            }
        }
    }
}

// animations rects data:
// enemy: 63x48 (offset 63 on x)
// boss: 48x48 (offset 48 on x)
// player: 32x14 (offset 32 on x and 14 on y to change color)
