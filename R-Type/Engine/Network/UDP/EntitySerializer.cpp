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
    this->serializeComponent<SyncID>(packet, std::any_cast<SyncID &>(componentManager.getComponent(typeid(SyncID)).getField(id).value()));

    // mask
    packet.push_back(InfoEntity::POS | InfoEntity::VEL | InfoEntity::SPRITEID);

    // components
    for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
        switch (i) {
        case 0:
            this->serializeComponent<Position>(packet, std::any_cast<Position &>(componentManager.getComponent(i).getField(id).value()));
            break;
        case 1:
            this->serializeComponent<Velocity>(packet, std::any_cast<Velocity &>(componentManager.getComponent(i).getField(id).value()));
            break;
        case 2:
            this->serializeComponent<SpriteID>(packet, std::any_cast<SpriteID &>(componentManager.getComponent(i).getField(id).value()));
            break;
        default:
            break;
        }
    }

    // footer
    for (auto elem : FOOTER) {
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
