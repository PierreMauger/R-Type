#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, Loader &loader)
{
    this->_clock = clock;
    this->_window = window;

    this->_sprites = loader.getSprites();
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t render = (InfoEntity::POS | InfoEntity::SPRITEID);
    std::size_t renderCooldown = (InfoEntity::SPRITEID | InfoEntity::PARENT | InfoEntity::COOLDOWNSHOOT);

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value()) {
            if ((masks[i].value() & render) == render) {
                Position &pos = std::any_cast<Position &>(componentManager.getComponent(typeid(Position)).getField(i).value());
                SpriteID &spriteId = std::any_cast<SpriteID &>(componentManager.getComponent(typeid(SpriteID)).getField(i).value());
                this->_sprites[spriteId.id].setPosition(pos.x, pos.y);
                this->_window->draw(this->_sprites[spriteId.id]);
            }
            if ((masks[i].value() & renderCooldown) == renderCooldown) {
                SpriteID &spriteId = std::any_cast<SpriteID &>(componentManager.getComponent(typeid(SpriteID)).getField(i).value());
                CooldownShoot &cooldownShoot = std::any_cast<CooldownShoot &>(componentManager.getComponent(typeid(CooldownShoot)).getField(i).value());
                sf::Sprite &spriteRef = this->_sprites.at(spriteId.id);
                spriteRef.setScale(((_clock->getElapsedTime().asSeconds() - cooldownShoot.time + cooldownShoot.cooldown) * 100 / cooldownShoot.cooldown) > 100
                                       ? 100
                                       : (_clock->getElapsedTime().asSeconds() - cooldownShoot.time + cooldownShoot.cooldown) * 100 / cooldownShoot.cooldown,
                                   1);
                this->_window->draw(this->_sprites[spriteId.id]);
            }
        }
    }
}
