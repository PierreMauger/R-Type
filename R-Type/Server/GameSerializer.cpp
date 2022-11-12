#include "GameSerializer.hpp"

using namespace eng;

GameSerializer::GameSerializer()
{
}

void GameSerializer::pushComponents(std::vector<uint8_t> &packet, std::size_t mask, std::size_t id, ComponentManager &componentManager)
{
    for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }
        switch (i) {
        case 0:
            this->serializeData<Position>(packet, &componentManager.getSingleComponent<Position>(id));
            break;
        case 1:
            this->serializeData<Velocity>(packet, &componentManager.getSingleComponent<Velocity>(id));
            break;
        case 2:
            this->serializeData<Size>(packet, &componentManager.getSingleComponent<Size>(id));
            break;
        case 3:
            this->serializeData<SpriteID>(packet, &componentManager.getSingleComponent<SpriteID>(id));
            break;
        case 4:
            this->serializeData<Controllable>(packet, &componentManager.getSingleComponent<Controllable>(id));
            break;
        case 5:
            this->serializeData<Parallax>(packet, &componentManager.getSingleComponent<Parallax>(id));
            break;
        case 6:
            this->serializeData<Projectile>(packet, &componentManager.getSingleComponent<Projectile>(id));
            break;
        case 7:
            this->serializeData<Life>(packet, &componentManager.getSingleComponent<Life>(id));
            break;
        case 8:
            this->serializeData<Enemy>(packet, &componentManager.getSingleComponent<Enemy>(id));
            break;
        case 9:
            this->serializeData<Appearance>(packet, &componentManager.getSingleComponent<Appearance>(id));
            break;
        case 10:
            this->serializeData<Disappearance>(packet, &componentManager.getSingleComponent<Disappearance>(id));
            break;
        case 11:
            this->serializeData<CooldownShoot>(packet, &componentManager.getSingleComponent<CooldownShoot>(id));
            break;
        case 12:
            this->serializeData<CooldownBar>(packet, &componentManager.getSingleComponent<CooldownBar>(id));
            break;
        case 13:
            this->serializeData<LifeBar>(packet, &componentManager.getSingleComponent<LifeBar>(id));
            break;
        case 14:
            this->serializeData<Parent>(packet, &componentManager.getSingleComponent<Parent>(id));
            break;
        case 15:
            this->serializeData<Pattern>(packet, &componentManager.getSingleComponent<Pattern>(id));
            break;
        case 16:
            this->serializeData<SyncID>(packet, &componentManager.getSingleComponent<SyncID>(id));
            break;
        case 17:
            this->serializeData<DropBonus>(packet, &componentManager.getSingleComponent<DropBonus>(id));
            break;
        case 18:
            this->serializeData<Text>(packet, &componentManager.getSingleComponent<Text>(id));
            break;
        case 19:
            this->serializeData<SoundID>(packet, &componentManager.getSingleComponent<SoundID>(id));
            break;
        case 20:
            this->serializeData<SpriteAttribut>(packet, &componentManager.getSingleComponent<SpriteAttribut>(id));
            break;
        case 21:
            this->serializeData<Button>(packet, &componentManager.getSingleComponent<Button>(id));
            break;
        case 22:
            this->serializeData<Shield>(packet, &componentManager.getSingleComponent<Shield>(id));
            break;
        case 23:
            this->serializeData<Scene>(packet, &componentManager.getSingleComponent<Scene>(id));
            break;
        default:
            break;
        }
    }
}

void GameSerializer::handlePacket(_STORAGE_DATA packet, EntityManager &entityManager, ComponentManager &componentManager, Graphic &graphic, Client &client, std::shared_ptr<std::size_t> syncId)
{
    std::size_t adv = 0;
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    GamePacketType type;

    if (!this->checkMagic(packetVector, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    adv += (MAGIC_SIZE + sizeof(std::size_t));
    this->deserializeData<GamePacketType>(packetVector, adv, &type);
    switch (type) {
    case ENTITY:
        break;
    case INPUT:
        this->deserializeInput(packetVector, entityManager, componentManager, graphic, client, syncId);
        break;
    default:
        throw std::runtime_error("[ERROR] Unknown packet type");
    }
}

_STORAGE_DATA GameSerializer::serializeEntity(std::size_t entityId, CrudType type, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::vector<uint8_t> packet;

    this->insertMagic(packet);

    // header
    GamePacketType gamePacketType = GamePacketType::ENTITY;
    this->serializeData(packet, &gamePacketType);
    this->serializeData(packet, &type);

    // sync id
    this->serializeData<SyncID>(packet, &componentManager.getSingleComponent<SyncID>(entityId));

    // mask
    if (entityId >= entityManager.getMasks().size()) {
        throw std::runtime_error("[ERROR] Entity id out of range");
    }
    std::optional<std::size_t> mask = entityManager.getMasks()[entityId];
    if (!mask.has_value()) {
        throw std::runtime_error("[ERROR] Entity has no mask");
    }
    this->serializeData<std::size_t>(packet, &mask.value());

    // components
    this->pushComponents(packet, mask.value(), entityId, componentManager);

    this->insertMagic(packet);
    return this->convertToData(packet);
}

void GameSerializer::deserializeInput(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager, Graphic &graphic, Client &client, std::shared_ptr<std::size_t> syncId)
{
    std::size_t adv = MAGIC_SIZE + sizeof(std::size_t) + sizeof(GamePacketType);
    sf::Keyboard::Key keyPress = sf::Keyboard::Key::Unknown;

    this->deserializeData<sf::Keyboard::Key>(packet, adv, &keyPress);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    if (static_cast<std::size_t>(client.getVesselId()) >= entityManager.getMasks().size()) {
        return;
    }

    auto &vel = componentManager.getSingleComponent<Velocity>(client.getVesselId());
    auto &sht = componentManager.getSingleComponent<CooldownShoot>(client.getVesselId());
    if (keyPress == sf::Keyboard::Key::Left) {
        vel.x += vel.baseSpeedX * -1;
        return;
    }
    if (keyPress == sf::Keyboard::Key::Right) {
        vel.x += vel.baseSpeedX;
        return;
    }
    if (keyPress == sf::Keyboard::Key::Up) {
        vel.y += vel.baseSpeedY * -1;
        return;
    }
    if (keyPress == sf::Keyboard::Key::Down) {
        vel.y += vel.baseSpeedY;
        return;
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && graphic.getClock()->getElapsedTime().asSeconds() > sht.lastShoot)) {
        std::size_t idPar = componentManager.getSingleComponent<SyncID>(client.getVesselId()).id;
        sht.lastShoot = graphic.getClock()->getElapsedTime().asSeconds() + sht.shootDelay;
        ProjectilePreload::createShoot(entityManager, componentManager, graphic.getWindow()->getSize(), graphic.getScreenSize(), {2, 15, 0, 0, idPar, *syncId});
        *syncId += 1;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && graphic.getClock()->getElapsedTime().asSeconds() > (sht.lastShoot - (sht.shootDelay / 2)))) {
        std::size_t idPar = componentManager.getSingleComponent<SyncID>(client.getVesselId()).id;
        sht.lastShoot = graphic.getClock()->getElapsedTime().asSeconds() + sht.shootDelay;
        ProjectilePreload::createShoot(entityManager, componentManager, graphic.getWindow()->getSize(), graphic.getScreenSize(), {1, 15, 0, 0, idPar, *syncId});
        *syncId += 1;
    }
}

std::size_t GameSerializer::getClientId(_STORAGE_DATA packet)
{
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    std::size_t adv = MAGIC_SIZE;
    std::size_t id;

    this->deserializeData(packetVector, adv, &id);
    return id;
}
