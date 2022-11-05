#include "ServerGameSerializer.hpp"

using namespace eng;

ServerGameSerializer::ServerGameSerializer()
{
}

void ServerGameSerializer::handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Client &client)
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
        this->deserializeInput(packetVector, id, entityManager, componentManager, client);
        break;
    default:
        throw std::runtime_error("[ERROR] Unknown packet type");
    }
}

void ServerGameSerializer::deserializeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Client &client)
{
    std::size_t adv = MAGIC_SIZE + sizeof(GamePacketType);
    sf::Keyboard::Key keyPress = sf::Keyboard::Key::Unknown;

    this->deserializeData<sf::Keyboard::Key>(packet, adv, &keyPress);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
}
