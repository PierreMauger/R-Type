#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, Loader &loader)
{
    this->_clock = clock;
    this->_window = window;
    this->_sprites = loader.getSprites();
}

void RenderSystem::displayCooldownBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    auto &masks = entityManager.getMasks();

    std::size_t cooldownBarParent = (InfoEntity::COOLDOWNBAR | InfoEntity::SPRITEID | InfoEntity::PARENT);
    std::size_t cooldownBarChild = (InfoEntity::COOLDOWNSHOOT);

    if (masks[i].has_value()) {
        if ((masks[i].value() & cooldownBarParent) == cooldownBarParent) {
            std::size_t idPar = std::any_cast<Parent &>(componentManager.getComponent(typeid(Parent)).getField(i).value()).id;
            if (masks[idPar].has_value()) {
                if ((masks[idPar].value() & cooldownBarChild) == cooldownBarChild) {
                    CooldownShoot &cooldownShoot = std::any_cast<CooldownShoot &>(componentManager.getComponent(typeid(CooldownShoot)).getField(idPar).value());
                    spriteRef.setScale(((this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * 100 / cooldownShoot.shootDelay) > 100
                                           ? 100
                                           : (this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * 100 / cooldownShoot.shootDelay,
                                       1);
                }
            } else
                spriteRef.setScale(0, 0);
        }
    }
}

void RenderSystem::displayLifeBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    auto &masks = entityManager.getMasks();

    std::size_t lifeBarParent = (InfoEntity::POS | InfoEntity::LIFEBAR | InfoEntity::PARENT);
    std::size_t lifeBarChild = (InfoEntity::POS | InfoEntity::LIFE | InfoEntity::SIZE);

    if (masks[i].has_value()) {
        if ((masks[i].value() & lifeBarParent) == lifeBarParent) {
            std::size_t idPar = std::any_cast<Parent &>(componentManager.getComponent(typeid(Parent)).getField(i).value()).id;
            if (masks[idPar].has_value()) {
                if ((masks[idPar].value() & lifeBarChild) == lifeBarChild) {
                    LifeBar &lifeBar = std::any_cast<LifeBar &>(componentManager.getComponent(typeid(LifeBar)).getField(i).value());
                    Life &life = std::any_cast<Life &>(componentManager.getComponent(typeid(Life)).getField(idPar).value());
                    Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(idPar).value());
                    Size &sz = std::any_cast<Size &>(componentManager.getComponent(typeid(Size)).getField(idPar).value());
                    spriteRef.setScale(life.life * sz.x / lifeBar.lifeMax, 1);
                    spriteRef.setPosition(pos.x, pos.y - 20);
                }
            } else
                spriteRef.setScale(0, 0);
        }
    }
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t render = (InfoEntity::POS | InfoEntity::SPRITEID);
    std::size_t renderCooldown = (InfoEntity::PARENT | InfoEntity::COOLDOWNBAR);
    std::size_t renderLife = (InfoEntity::PARENT | InfoEntity::LIFEBAR);
    std::size_t renderParallax = (InfoEntity::POS | InfoEntity::SPRITEID | InfoEntity::PARALLAX);
    std::size_t renderProj = (InfoEntity::PROJECTILE);
    std::vector<sf::Sprite> stockSpriteHigh;
    std::vector<sf::Sprite> stockSpriteMedium;
    std::vector<sf::Sprite> stockSpriteLow;

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & render) == render) {
            Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
            SpriteID &spriteId = std::any_cast<SpriteID &>(componentManager.getComponent(typeid(SpriteID)).getField(i).value());
            this->_sprites[spriteId.id].setPosition(pos.x, pos.y);
            sf::Sprite &spriteRef = this->_sprites[std::any_cast<SpriteID &>(componentManager.getComponent(typeid(SpriteID)).getField(i).value()).id];
            if ((masks[i].value() & renderCooldown) == renderCooldown)
                displayCooldownBar(componentManager, entityManager, spriteRef, i);
            if ((masks[i].value() & renderLife) == renderLife)
                displayLifeBar(componentManager, entityManager, spriteRef, i);
            if ((masks[i].value() & renderProj) == renderProj) {
                Projectile &proj = std::any_cast<Projectile &>(componentManager.getComponent(typeid(Projectile)).getField(i).value());
                spriteRef.setScale(proj.size, proj.size);
            }
            if (spriteId.priority == Priority::HIGH)
                stockSpriteHigh.push_back(spriteRef);
            if (spriteId.priority == Priority::MEDIUM)
                stockSpriteMedium.push_back(spriteRef);
            if (spriteId.priority == Priority::LOW)
                stockSpriteLow.push_back(spriteRef);
        }
    }
    for (std::size_t i = 0; i < stockSpriteHigh.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & renderParallax) == renderParallax) {
            stockSpriteHigh[i].setPosition(stockSpriteHigh[i].getPosition().x + _window->getSize().x, stockSpriteHigh[i].getPosition().y);
            this->_window->draw(stockSpriteHigh[i]);
            stockSpriteHigh[i].setPosition(stockSpriteHigh[i].getPosition().x - _window->getSize().x, stockSpriteHigh[i].getPosition().y);
        }
        this->_window->draw(stockSpriteHigh[i]);
    }
    for (std::size_t i = 0; i < stockSpriteMedium.size(); i++)
        this->_window->draw(stockSpriteMedium[i]);
    for (std::size_t i = 0; i < stockSpriteLow.size(); i++)
        this->_window->draw(stockSpriteLow[i]);
}
