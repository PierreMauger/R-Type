#include "Engine/Network/UDP/EntitySerializer.hpp"

eng::EntitySerializer::EntitySerializer()
{
}

std::vector<uint8_t> eng::EntitySerializer::serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager)
{
    std::vector<uint8_t> packet;

    // header
    packet.push_back(ENTITY);
    packet.push_back(type);

    // sync id
    this->serializeComponent<SyncID>(packet, componentManager.getSingleComponent<SyncID &>(id));

    // mask
    packet.push_back(InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID);

    // components
    for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
        switch (i) {
        case 0:
            this->serializeComponent<Position>(packet, componentManager.getSingleComponent<Position &>(id));
            break;
        case 1:
            this->serializeComponent<Velocity>(packet, componentManager.getSingleComponent<Velocity &>(id));
            break;
        case 2:
            this->serializeComponent<SpriteID>(packet, componentManager.getSingleComponent<SpriteID &>(id));
            break;
        default:
            break;
        }
    }

    // footer
    for (auto elem : MAGIC_NUMBER) {
        packet.push_back(elem);
    }

    return packet;
}

void eng::EntitySerializer::synchronizeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager)
{
    if (packet.at(0) != ENTITY) {
        return;
    }

    std::size_t adv = 1;
    EntityType type = static_cast<EntityType>(packet.at(adv++));

    std::cout << "type: " << type << std::endl;
}
