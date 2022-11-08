#include "GameSerializer.hpp"

using namespace eng;

GameSerializer::GameSerializer()
{
}

void GameSerializer::getComponents(std::vector<uint8_t> &packet, std::size_t id, std::size_t mask, std::size_t &adv, ComponentManager &componentManager)
{
    for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }
        switch (i) {
        case 0:
            this->updateEntity<Position>(packet, id, adv, componentManager);
            break;
        case 1:
            this->updateEntity<Velocity>(packet, id, adv, componentManager);
            break;
        case 2:
            this->updateEntity<Size>(packet, id, adv, componentManager);
            break;
        case 3:
            this->updateEntity<SpriteID>(packet, id, adv, componentManager);
            break;
        case 4:
            this->updateEntity<Controllable>(packet, id, adv, componentManager);
            break;
        case 5:
            this->updateEntity<Parallax>(packet, id, adv, componentManager);
            break;
        case 6:
            this->updateEntity<Projectile>(packet, id, adv, componentManager);
            break;
        case 7:
            this->updateEntity<Life>(packet, id, adv, componentManager);
            break;
        case 8:
            this->updateEntity<Enemy>(packet, id, adv, componentManager);
            break;
        case 9:
            this->updateEntity<Appearance>(packet, id, adv, componentManager);
            break;
        case 10:
            this->updateEntity<Disappearance>(packet, id, adv, componentManager);
            break;
        case 11:
            this->updateEntity<CooldownShoot>(packet, id, adv, componentManager);
            break;
        case 12:
            this->updateEntity<CooldownBar>(packet, id, adv, componentManager);
            break;
        case 13:
            this->updateEntity<LifeBar>(packet, id, adv, componentManager);
            break;
        case 14:
            this->updateEntity<Parent>(packet, id, adv, componentManager);
            break;
        case 15:
            this->updateEntity<Pattern>(packet, id, adv, componentManager);
            break;
        case 16:
            this->updateEntity<SyncID>(packet, id, adv, componentManager);
            break;
        case 17:
            this->updateEntity<DropBonus>(packet, id, adv, componentManager);
            break;
        case 18:
            this->updateEntity<Text>(packet, id, adv, componentManager);
            break;
        case 19:
            this->updateEntity<SoundID>(packet, id, adv, componentManager);
            break;
        case 20:
            this->updateEntity<SpriteAttribut>(packet, id, adv, componentManager);
            break;
        case 21:
            this->updateEntity<Button>(packet, id, adv, componentManager);
            break;
        default:
            break;
        }
    }
}

void GameSerializer::handlePacket(_STORAGE_DATA packet, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t adv = 0;
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    GamePacketType type;

    if (!this->checkMagic(packetVector, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    adv += MAGIC_SIZE;
    this->deserializeData<GamePacketType>(packetVector, adv, &type);
    switch (type) {
    case ENTITY:
        this->deserializeEntity(packetVector, entityManager, componentManager);
        break;
    case INPUT:
        break;
    default:
        throw std::runtime_error("[ERROR] Unknown packet type");
    }
}

void GameSerializer::deserializeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t adv = MAGIC_SIZE + sizeof(GamePacketType);
    CrudType type = CrudType::UNKNOWN;
    SyncID syncID = {0};
    std::size_t mask = 0;
    std::size_t id = 0;

    this->deserializeData<CrudType>(packet, adv, &type);
    this->deserializeData<SyncID>(packet, adv, &syncID);
    this->deserializeData<std::size_t>(packet, adv, &mask);

    id = entityManager.getBySyncId(syncID.id, componentManager);

    if (id == entityManager.getMasks().size()) {
        id = entityManager.addMask(mask, componentManager);
        componentManager.addComponent<SyncID>(id);
        componentManager.getSingleComponent<SyncID>(id) = syncID;
    }
    if (type == CrudType::DESTROY) {
        componentManager.removeAllComponents(id);
        entityManager.removeMask(id);
    } else if (type == CrudType::UPDATE) {
        this->getComponents(packet, id, mask, adv, componentManager);
    } else {
        throw std::runtime_error("[ERROR] Unknown entity type");
    }
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
}

_STORAGE_DATA GameSerializer::serializeInput(sf::Keyboard::Key input)
{
    std::vector<uint8_t> packet;
    GamePacketType type = GamePacketType::INPUT;

    this->insertMagic(packet);

    this->serializeData<GamePacketType>(packet, &type);
    this->serializeData<sf::Keyboard::Key>(packet, &input);

    this->insertMagic(packet);
    return this->convertToData(packet);
}
