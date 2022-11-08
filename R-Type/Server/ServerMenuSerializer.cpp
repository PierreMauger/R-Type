#include "ServerMenuSerializer.hpp"

using namespace eng;

ServerMenuSerializer::ServerMenuSerializer()
{
}

void ServerMenuSerializer::handlePacket(_STORAGE_DATA packet, std::vector<Room> &rooms, Client &client, std::size_t &roomCount)
{
    std::size_t adv = 0;
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    MenuPacketType type;

    if (!this->checkMagic(packetVector, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    adv += MAGIC_SIZE;
    this->deserializeData<MenuPacketType>(packetVector, adv, &type);

    switch (type) {
    case MenuPacketType::ROOM_EDIT:
        this->deserializeRoomEdit(packetVector, rooms, roomCount);
        break;
    case MenuPacketType::ROOM_ACTION:
        this->deserializeRoomAction(packetVector, rooms, client);
        break;
    case MenuPacketType::EVENT:
        this->deserializeEvent();
        break;
    default:
        throw std::runtime_error("[ERROR] Invalid packet type");
    }
}

void ServerMenuSerializer::deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms, Client &client)
{
    std::size_t adv = MAGIC_SIZE + sizeof(MenuPacketType);
    std::size_t id;
    RoomAction action;

    this->deserializeData(packet, adv, &action);
    this->deserializeData(packet, adv, &id);

    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }

    auto roomIt = getRoom(rooms, id);

    switch (action) {
    case RoomAction::JOIN:
        client.setRoomId(roomIt->getId());
        roomIt->addPlayer();
        break;
    case RoomAction::LEAVE:
        client.setRoomId(-1);
        client.setReady(false);
        roomIt->removePlayer();
        break;
    case RoomAction::READY:
        if (client.getRoomId() == -1)
            break;
        client.setReady(true);
        break;
    case RoomAction::UNREADY:
        if (client.getRoomId() == -1)
            break;
        client.setReady(false);
        break;
    default:
        break;
    }
}

void ServerMenuSerializer::deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms, std::size_t &roomCount)
{
    std::size_t adv = MAGIC_SIZE + sizeof(MenuPacketType);
    std::size_t id;
    std::size_t maxPlayers;
    std::size_t nbPlayers;
    CrudType crudType;

    this->deserializeData(packet, adv, &crudType);
    this->deserializeData(packet, adv, &id);
    this->deserializeData(packet, adv, &maxPlayers);
    this->deserializeData(packet, adv, &nbPlayers);

    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }

    auto roomIt = getRoom(rooms, id);

    if (roomIt == rooms.end()) {
        id = roomCount++;
    }
    this->editRoom(crudType, rooms, id, maxPlayers, nbPlayers);
}

void ServerMenuSerializer::deserializeEvent()
{
    // TODO
}
