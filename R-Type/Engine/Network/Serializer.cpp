#include "Engine/Network/Serializer.hpp"

eng::Serializer::Serializer()
{
}

std::size_t eng::Serializer::insertMagic(_STORAGE_DATA &packet, std::size_t adv)
{
    for (std::size_t i = 0; i < MAGIC_SIZE; i++) {
        packet[adv + i] = (uint8_t)MAGIC[i];
    }
    return adv + MAGIC_SIZE;
}

bool eng::Serializer::checkMagic(_STORAGE_DATA &packet, std::size_t adv)
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
        if (masks[id].has_value() && (masks[id].value() & InfoComp::SYNCID) && componentManager.getSingleComponent<SyncID &>(id).id == syncID.id) {
            return id;
        }
    }
    throw std::runtime_error("[ERROR] SyncID not found");
}

std::size_t eng::Serializer::updateEntity(_STORAGE_DATA &packet, std::size_t id, std::size_t adv, ComponentManager &componentManager)
{
    Position pos = {0, 0};
    Velocity vel = {0, 0};
    SpriteID spriteID = {0};

    adv = this->deserializeComponent<Position>(packet, adv, pos);
    adv = this->deserializeComponent<Velocity>(packet, adv, vel);
    adv = this->deserializeComponent<SpriteID>(packet, adv, spriteID);
    componentManager.getSingleComponent<Position &>(id) = pos;
    componentManager.getSingleComponent<Velocity &>(id) = vel;
    componentManager.getSingleComponent<SpriteID &>(id) = spriteID;
    return adv;
}

_STORAGE_DATA eng::Serializer::serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager)
{
    _STORAGE_DATA packet = {0};
    std::size_t adv = 0;

    adv = this->insertMagic(packet, adv);

    // header
    packet[adv++] = (uint8_t)ENTITY;
    packet[adv++] = (uint8_t)type;

    // sync id

    adv = this->serializeComponent<SyncID>(packet, adv, componentManager.getSingleComponent<SyncID &>(id));

    // mask
    std::size_t editMask = static_cast<std::size_t>(InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID);
    adv = this->serializeComponent<std::size_t>(packet, adv, editMask);

    // components
    adv = this->serializeComponent<Position>(packet, adv, componentManager.getSingleComponent<Position &>(id));
    adv = this->serializeComponent<Velocity>(packet, adv, componentManager.getSingleComponent<Velocity &>(id));
    adv = this->serializeComponent<SpriteID>(packet, adv, componentManager.getSingleComponent<SpriteID &>(id));

    adv = this->insertMagic(packet, adv);
    return packet;
}

void eng::Serializer::synchronizeEntity(_STORAGE_DATA packet, EntityManager &entityManager, ComponentManager &componentManager)
{
    // skip magic and header
    std::size_t adv = MAGIC_SIZE + sizeof(uint8_t);
    // fields
    EntityType type;
    SyncID syncID = {0};
    std::size_t mask = 0;
    std::size_t id = 0;

    type = static_cast<EntityType>(packet[adv++]);
    adv = this->deserializeComponent<SyncID>(packet, adv, syncID);
    adv = this->deserializeComponent<std::size_t>(packet, adv, mask);

    if (type == EntityType::DESTROY) {
        id = this->getEntityID(syncID, entityManager, componentManager);
        entityManager.removeMask(id);
        componentManager.removeAllComponents(id);
        return;
    }
    if (type == EntityType::CREATE) {
        id = entityManager.addMask(mask, componentManager);
        componentManager.getSingleComponent<SyncID &>(id) = syncID;
    } else if (type == EntityType::UPDATE) {
        id = this->getEntityID(syncID, entityManager, componentManager);
    } else {
        throw std::runtime_error("[ERROR] Unknown entity type");
    }
    this->updateEntity(packet, id, adv, componentManager);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
}

_STORAGE_DATA eng::Serializer::serializeInput(sf::Keyboard::Key input)
{
    std::size_t adv = 0;
    _STORAGE_DATA packet = {0};

    adv = this->insertMagic(packet, adv);

    packet[adv++] = INPUT;
    adv = this->serializeComponent<sf::Keyboard::Key>(packet, adv, input);
    adv = this->insertMagic(packet, adv);
    return packet;
}

void eng::Serializer::synchronizeInput(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                       std::shared_ptr<sf::Clock> clock)
{
    std::size_t adv = MAGIC_SIZE + sizeof(uint8_t);
    sf::Keyboard::Key keyPress;

    adv = this->deserializeComponent<sf::Keyboard::Key>(packet, adv, keyPress);
    input.checkInput(id, keyPress, componentManager, entityManager, clock);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
}

void eng::Serializer::handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                   std::shared_ptr<sf::Clock> clock)
{
    std::size_t adv = 0;

    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    adv += MAGIC_SIZE;
    switch (packet[adv]) {
    case ENTITY:
        this->synchronizeEntity(packet, entityManager, componentManager);
        break;
    case INPUT:
        this->synchronizeInput(packet, id, entityManager, componentManager, input, clock);
        break;
    default:
        throw std::runtime_error("[ERROR] Unknown packet type");
    }
}
