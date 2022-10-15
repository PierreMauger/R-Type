#include "Engine/Network/UDP/EntitySerializer.hpp"

eng::EntitySerializer::EntitySerializer()
{
}

void eng::EntitySerializer::insertMagic(std::vector<uint8_t> &packet)
{
    for (auto elem : MAGIC) {
        packet.push_back(elem);
    }
}

std::size_t eng::EntitySerializer::getEntityID(SyncID syncID, EntityManager &entityManager, ComponentManager &componentManager)
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

std::size_t eng::EntitySerializer::updateEntity(std::vector<uint8_t> &packet, std::size_t id, std::size_t &adv, ComponentManager &componentManager)
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

std::vector<uint8_t> eng::EntitySerializer::serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager)
{
    std::vector<uint8_t> packet;

    this->insertMagic(packet);

    // header
    packet.push_back(ENTITY);
    packet.push_back(type);

    // sync id
    this->serializeComponent<SyncID>(packet, componentManager.getSingleComponent<SyncID &>(id));

    // mask
    std::size_t editMask = static_cast<std::size_t>(InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID);
    this->serializeComponent<std::size_t>(packet, editMask);

    std::cout << "mask " << editMask << std::endl;

    // components
    this->serializeComponent<Position>(packet, componentManager.getSingleComponent<Position &>(id));
    this->serializeComponent<Velocity>(packet, componentManager.getSingleComponent<Velocity &>(id));
    this->serializeComponent<SpriteID>(packet, componentManager.getSingleComponent<SpriteID &>(id));

    this->insertMagic(packet);
    return packet;
}

void eng::EntitySerializer::synchronizeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager)
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
    adv = this->updateEntity(packet, id, adv, componentManager);
}
