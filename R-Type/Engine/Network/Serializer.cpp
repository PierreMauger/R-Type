#include "Engine/Network/Serializer.hpp"

eng::Serializer::Serializer()
{
}

void eng::Serializer::insertMagic(std::vector<uint8_t> &packet)
{
    for (auto elem : MAGIC) {
        // packet.push_back(elem);
    }
}

bool eng::Serializer::checkMagic(std::vector<uint8_t> &packet, std::size_t adv)
{
    for (std::size_t i = 0; i < MAGIC_SIZE; i++) {
        if (packet[adv + i] != MAGIC[i]) {
            return false;
        }
    }
    return true;
}

std::size_t eng::Serializer::getEntityID(SyncID syncID, EntityManager &entityManager, ComponentManager &componentManager)
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

std::size_t eng::Serializer::updateEntity(std::vector<uint8_t> &packet, std::size_t id, std::size_t &adv, ComponentManager &componentManager)
{
    Position pos = {0, 0};
    adv = this->deserializeComponent<Position>(packet, adv, &pos);
    componentManager.getSingleComponent<Position>(id) = pos;

    Velocity vel = {0, 0};
    adv = this->deserializeComponent<Velocity>(packet, adv, &vel);
    componentManager.getSingleComponent<Velocity>(id) = vel;

    SpriteID spriteID = {0};
    adv = this->deserializeComponent(packet, adv, &spriteID);
    componentManager.getSingleComponent<SpriteID>(id) = spriteID;
    return adv;
}

_STORAGE_DATA eng::Serializer::convertToArray(std::vector<uint8_t> &packet)
{
    _STORAGE_DATA convert = {0};

    for (std::size_t i = 0; i < packet.size(); i++) {
        convert[i] = packet[i];
    }
    return convert;
}

std::vector<uint8_t> eng::Serializer::convertToVector(_STORAGE_DATA &packet)
{
    std::vector<uint8_t> convert;

    for (std::size_t i = 0; i < packet.size(); i++) {
        convert.push_back(packet[i]);
    }
    return convert;
}

_STORAGE_DATA eng::Serializer::serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager)
{
    std::vector<uint8_t> packet;

    this->insertMagic(packet);

    // header
    PacketType packetType = ENTITY;
    this->serializeComponent(packet, &packetType);
    this->serializeComponent(packet, &type);

    // sync id
    this->serializeComponent<SyncID>(packet, &componentManager.getSingleComponent<SyncID>(id));

    // mask
    std::size_t editMask = static_cast<std::size_t>(InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID);
    this->serializeComponent<std::size_t>(packet, &editMask);

    // components
    this->serializeComponent<Position>(packet, &componentManager.getSingleComponent<Position>(id));
    this->serializeComponent<Velocity>(packet, &componentManager.getSingleComponent<Velocity>(id));
    this->serializeComponent<SpriteID>(packet, &componentManager.getSingleComponent<SpriteID>(id));

    this->insertMagic(packet);
    return this->convertToArray(packet);
}

void eng::Serializer::synchronizeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager)
{
    // skip magic and header
    std::size_t adv = MAGIC_SIZE + sizeof(PacketType);
    // fields
    EntityType type;
    SyncID syncID = {0};
    std::size_t mask = 0;
    std::size_t id = 0;

    adv = this->deserializeComponent<EntityType>(packet, adv, &type);
    adv = this->deserializeComponent<SyncID>(packet, adv, &syncID);
    adv = this->deserializeComponent<std::size_t>(packet, adv, &mask);

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
    adv = this->updateEntity(packet, id, adv, componentManager);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
}

_STORAGE_DATA eng::Serializer::serializeInput(sf::Keyboard::Key input)
{
    std::vector<uint8_t> packet;
    PacketType type = INPUT;

    this->insertMagic(packet);

    this->serializeComponent<PacketType>(packet, &type);
    this->serializeComponent<sf::Keyboard::Key>(packet, &input);

    this->insertMagic(packet);
    return this->convertToArray(packet);
}

void eng::Serializer::synchronizeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                       std::shared_ptr<sf::Clock> clock)
{
    std::size_t adv = MAGIC_SIZE + sizeof(PacketType);
    sf::Keyboard::Key keyPress;

    adv = this->deserializeComponent<sf::Keyboard::Key>(packet, adv, &keyPress);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    input.checkInput(id, keyPress, componentManager, entityManager, clock);
}

void eng::Serializer::handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                   std::shared_ptr<sf::Clock> clock)
{
    std::size_t adv = 0;
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    PacketType type;

    if (!this->checkMagic(packetVector, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    adv += MAGIC_SIZE;
    adv = this->deserializeComponent<PacketType>(packetVector, adv, &type);

    std::cout << "Packet type: " << type << std::endl;
    switch (type) {
    case ENTITY:
        this->synchronizeEntity(packetVector, entityManager, componentManager);
        break;
    case INPUT:
        this->synchronizeInput(packetVector, id, entityManager, componentManager, input, clock);
        break;
    default:
        throw std::runtime_error("[ERROR] Unknown packet type");
    }
}
