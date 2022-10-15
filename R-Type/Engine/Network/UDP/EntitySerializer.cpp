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

std::size_t eng::EntitySerializer::getEntityID(SyncID syncID, ComponentManager &componentManager)
{
    std::size_t id = 0;
    Component &syncIDs = componentManager.getComponentArray()[typeid(SyncID)];

    for (; id < syncIDs.getSize(); id++) {
        if (!syncIDs.getField(id).has_value()) {
            continue;
        }
        if (std::any_cast<SyncID>(syncIDs.getField(id).value()).id == syncID.id) {
            return id;
        }
    }
    throw std::runtime_error("[ERROR] SyncID not found");
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

    type = static_cast<EntityType>(packet[adv]);
    adv = this->deserializeComponent<SyncID>(packet, adv, syncID);
    adv = this->deserializeComponent<std::size_t>(packet, adv, mask);

    // TODO
    switch (type) {
    case EntityType::CREATE:
        break;
    case EntityType::DESTROY:
        break;
    case EntityType::UPDATE:
        break;
    }
}
