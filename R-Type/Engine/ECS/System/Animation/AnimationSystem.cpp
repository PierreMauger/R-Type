#include "Engine/ECS/System/Animation/AnimationSystem.hpp"

using namespace eng;

AnimationSystem::AnimationSystem(std::shared_ptr<sf::Event> event, std::shared_ptr<sf::Clock> clock, std::shared_ptr<std::vector<sf::Sprite>> sprites)
{
    this->_event = event;
    this->_clock = clock;
    this->_sprites = sprites;
    this->_sprites->at(2).setTextureRect(sf::IntRect(0, 0, 63, 48));
    this->_sprites->at(5).setTextureRect(sf::IntRect(0, 0, 96, 96));
    this->_sprites->at(6).setTextureRect(sf::IntRect(0, 0, 64, 28));
}

void AnimationSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t spriteMask = (InfoComp::SPRITEID | InfoComp::SIZE);
    std::size_t appMask = (InfoComp::APP);
    std::size_t contMask = (InfoComp::CONTROLLABLE);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & spriteMask) == spriteMask) {
            SpriteID &spriteID = componentManager.getSingleComponent<SpriteID>(i);
            Size &sz = componentManager.getSingleComponent<Size>(i);
            if (masks[i].has_value() && (masks[i].value() & contMask) == contMask) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    this->_sprites->at(spriteID.id).setTextureRect(sf::IntRect(spriteID.offsetX * 2, 0, sz.x, sz.y));
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    this->_sprites->at(spriteID.id).setTextureRect(sf::IntRect(spriteID.offsetX, 0, sz.x, sz.y));
                else
                    this->_sprites->at(spriteID.id).setTextureRect(sf::IntRect(0, 0, sz.x, sz.y));
                continue;
            }
            if (spriteID.nbFrame == 0 || ((masks[i].value() & appMask) == appMask && componentManager.getSingleComponent<Appearance>(i).app))
                continue;
            if (this->_clock->getElapsedTime().asSeconds() >= spriteID.lastTime + spriteID.delay) {
                if (spriteID.curFrame == 0)
                    spriteID.signe = false;
                if (spriteID.curFrame == spriteID.nbFrame)
                    spriteID.signe = true;
                spriteID.signe == false ? spriteID.curFrame++ : spriteID.curFrame--;
                this->_sprites->at(spriteID.id).setTextureRect(sf::IntRect(spriteID.curFrame * spriteID.offsetX, spriteID.curFrame * spriteID.offsetY, sz.x, sz.y));
                spriteID.lastTime = this->_clock->getElapsedTime().asSeconds();
                // bug anim synchro
            }
        }
    }
}

// animations rects data:
// enemy: 63x48 (offset 63 on x)
// boss: 48x48 (offset 48 on x)
// player: 32x14 (offset 32 on x and 14 on y to change color)