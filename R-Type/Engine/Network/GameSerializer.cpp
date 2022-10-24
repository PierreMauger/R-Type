#include "Engine/Network/GameSerializer.hpp"

eng::GameSerializer::GameSerializer()
{
}

std::size_t eng::GameSerializer::getEntityID(SyncID syncID, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t id = 0;
    auto masks = entityManager.getMasks();

    for (; id < masks.size(); id++) {
        if (masks[id].has_value() && (masks[id].value() & InfoComp::SYNCID) && componentManager.getSingleComponent<SyncID>(id).id == syncID.id) {
            return id;
        }
    }
    throw std::runtime_error("[ERROR] SyncID not found");
}

void eng::GameSerializer::pushComponents(std::vector<uint8_t> &packet, std::size_t mask, std::size_t id, ComponentManager &componentManager)
{
    for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }
        switch (i) {
        case 0:
            this->serializeComponent<Position>(packet, &componentManager.getSingleComponent<Position>(id));
            break;
        case 1:
            this->serializeComponent<Velocity>(packet, &componentManager.getSingleComponent<Velocity>(id));
            break;
        case 2:
            this->serializeComponent<Size>(packet, &componentManager.getSingleComponent<Size>(id));
            break;
        case 3:
            this->serializeComponent<SpriteID>(packet, &componentManager.getSingleComponent<SpriteID>(id));
            break;
        case 4:
            this->serializeComponent<Controllable>(packet, &componentManager.getSingleComponent<Controllable>(id));
            break;
        case 5:
            this->serializeComponent<Parallax>(packet, &componentManager.getSingleComponent<Parallax>(id));
            break;
        case 6:
            this->serializeComponent<Projectile>(packet, &componentManager.getSingleComponent<Projectile>(id));
            break;
        case 7:
            this->serializeComponent<Life>(packet, &componentManager.getSingleComponent<Life>(id));
            break;
        case 8:
            this->serializeComponent<Enemy>(packet, &componentManager.getSingleComponent<Enemy>(id));
            break;
        case 9:
            this->serializeComponent<Appearance>(packet, &componentManager.getSingleComponent<Appearance>(id));
            break;
        case 10:
            this->serializeComponent<Disappearance>(packet, &componentManager.getSingleComponent<Disappearance>(id));
            break;
        case 11:
            this->serializeComponent<CooldownShoot>(packet, &componentManager.getSingleComponent<CooldownShoot>(id));
            break;
        case 12:
            this->serializeComponent<CooldownBar>(packet, &componentManager.getSingleComponent<CooldownBar>(id));
            break;
        case 13:
            this->serializeComponent<LifeBar>(packet, &componentManager.getSingleComponent<LifeBar>(id));
            break;
        case 14:
            this->serializeComponent<Parent>(packet, &componentManager.getSingleComponent<Parent>(id));
            break;
        case 15:
            this->serializeComponent<Patern>(packet, &componentManager.getSingleComponent<Patern>(id));
            break;
        case 16:
            this->serializeComponent<SyncID>(packet, &componentManager.getSingleComponent<SyncID>(id));
            break;
        case 17:
            this->serializeComponent<DropBonus>(packet, &componentManager.getSingleComponent<DropBonus>(id));
            break;
        case 18:
            this->serializeComponent<Text>(packet, &componentManager.getSingleComponent<Text>(id));
            break;
        case 19:
            this->serializeComponent<SoundID>(packet, &componentManager.getSingleComponent<SoundID>(id));
            break;
        case 20:
            this->serializeComponent<SpriteAttribut>(packet, &componentManager.getSingleComponent<SpriteAttribut>(id));
            break;
        default:
            break;
        }
    }
}

void eng::GameSerializer::getComponents(std::vector<uint8_t> &packet, std::size_t id, std::size_t mask, std::size_t &adv, ComponentManager &componentManager)
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
            this->updateEntity<Patern>(packet, id, adv, componentManager);
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
        default:
            break;
        }
    }
}

_STORAGE_DATA eng::GameSerializer::serializeEntity(std::size_t id, EntityType type, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::vector<uint8_t> packet;

    this->insertMagic(packet);

    // header
    PacketType packetType = PacketType::ENTITY;
    this->serializeComponent(packet, &packetType);
    this->serializeComponent(packet, &type);

    // sync id
    this->serializeComponent<SyncID>(packet, &componentManager.getSingleComponent<SyncID>(id));

    // mask
    std::optional<std::size_t> mask = entityManager.getMasks()[id];
    if (!entityManager.getMasks()[id].has_value()) {
        throw std::runtime_error("[ERROR] Entity has no mask");
    }
    this->serializeComponent<std::size_t>(packet, &entityManager.getMasks()[id].value());

    // components
    this->pushComponents(packet, mask.value(), id, componentManager);

    this->insertMagic(packet);
    return this->convertToData(packet);
}

void eng::GameSerializer::deserializeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t adv = MAGIC_SIZE + sizeof(PacketType);
    EntityType type = EntityType::UNKNOWN_ENTITY;
    SyncID syncID = {0};
    std::size_t mask = 0;
    std::size_t id = 0;

    this->deserializeComponent<EntityType>(packet, adv, &type);
    this->deserializeComponent<SyncID>(packet, adv, &syncID);
    this->deserializeComponent<std::size_t>(packet, adv, &mask);

    if (type == EntityType::DESTROY) {
        id = this->getEntityID(syncID, entityManager, componentManager);
        entityManager.removeMask(id);
        componentManager.removeAllComponents(id);
        return;
    }
    if (type == EntityType::CREATE) {
        id = entityManager.addMask(mask, componentManager);
        componentManager.getSingleComponent<SyncID>(id) = syncID;
    } else if (type == EntityType::UPDATE) {
        id = this->getEntityID(syncID, entityManager, componentManager);
    } else {
        throw std::runtime_error("[ERROR] Unknown entity type");
    }
    this->getComponents(packet, id, mask, adv, componentManager);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
}

_STORAGE_DATA eng::GameSerializer::serializeInput(sf::Keyboard::Key input)
{
    std::vector<uint8_t> packet;
    PacketType type = PacketType::INPUT;

    this->insertMagic(packet);

    this->serializeComponent<PacketType>(packet, &type);
    this->serializeComponent<sf::Keyboard::Key>(packet, &input);

    this->insertMagic(packet);
    return this->convertToData(packet);
}

void eng::GameSerializer::deserializeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                           std::shared_ptr<sf::Clock> clock)
{
    std::size_t adv = MAGIC_SIZE + sizeof(PacketType);
    sf::Keyboard::Key keyPress = sf::Keyboard::Key::Unknown;

    this->deserializeComponent<sf::Keyboard::Key>(packet, adv, &keyPress);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    input.checkInput(id, keyPress, componentManager, entityManager, clock);
}

void eng::GameSerializer::handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                       std::shared_ptr<sf::Clock> clock)
{
    std::size_t adv = 0;
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    PacketType type;

    if (!this->checkMagic(packetVector, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    adv += MAGIC_SIZE;
    this->deserializeComponent<PacketType>(packetVector, adv, &type);
    switch (type) {
    case ENTITY:
        this->deserializeEntity(packetVector, entityManager, componentManager);
        break;
    case INPUT:
        this->deserializeInput(packetVector, id, entityManager, componentManager, input, clock);
        break;
    default:
        throw std::runtime_error("[ERROR] Unknown packet type");
    }
}
