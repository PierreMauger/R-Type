#include "Engine/Network/UDP/EntitySerializer.hpp"

eng::EntitySerializer::EntitySerializer()
{
}

template <typename T> void eng::EntitySerializer::serializeComponent(std::vector<uint8_t> &packet, T &component)
{
    for (uint8_t i = 0; i < sizeof(T); i++) {
        packet.push_back(((uint8_t *)&component)[i]);
    }
}

template <typename T> std::size_t eng::EntitySerializer::deserializeComponent(std::vector<uint8_t> &packet, T &component)
{
    std::size_t i = 0;

    for (; i < sizeof(T); i++) {
        ((std::size_t *)&component)[i] = packet[i];
    }
    return i;
}

std::vector<uint8_t> eng::EntitySerializer::serializeEntity(std::size_t id, EntityType type, ComponentManager &componentManager)
{
    std::vector<uint8_t> packet;

    // header
    packet.push_back(ENTITY);
    packet.push_back(type);

    // sync id
    packet.push_back(std::any_cast<uint8_t>(componentManager.getComponent(typeid(SyncID)).getField(id)));

    // mask
    packet.push_back(eng::InfoEntity::POS | eng::InfoEntity::VEL);

    // components
    this->serializeComponent(packet, componentManager.getComponent(typeid(Position)).getField(id));
    this->serializeComponent(packet, componentManager.getComponent(typeid(Velocity)).getField(id));

    return packet;
}
