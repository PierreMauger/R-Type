#include "MenuSerializer.hpp"

using namespace eng;

MenuSerializer::MenuSerializer()
{
}

std::vector<Room>::iterator MenuSerializer::getRoom(std::vector<Room> rooms, int id)
{
    std::vector<Room>::iterator it;

    for (it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->getId() == id) {
            return it;
        }
    }
    return it;
}

void MenuSerializer::editRoom(CrudType crudType, std::vector<Room> &rooms, int id, std::size_t maxPlayers, std::size_t nbPlayers)
{
    auto roomIt = getRoom(rooms, id);

    if (roomIt == rooms.end()) {
        rooms.push_back(Room(id, maxPlayers, nbPlayers));
    }
    if (crudType == CrudType::UPDATE) {
        roomIt->setNbPlayers(nbPlayers);
        roomIt->setMaxPlayers(maxPlayers);
        return;
    }
    if (crudType == CrudType::DESTROY) {
        rooms.erase(roomIt);
        return;
    }
    throw std::runtime_error("[ERROR] Invalid CRUD type");
}

void MenuSerializer::handlePacket(_STORAGE_DATA packet, std::vector<Room> &rooms, std::size_t &roomCount)
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
        break;
    case MenuPacketType::EVENT:
        this->deserializeEvent(packetVector);
        break;
    default:
        throw std::runtime_error("[ERROR] Invalid packet type");
    }
}

_STORAGE_DATA MenuSerializer::serializeRoomEdit(std::size_t clientId, CrudType editType, Room &room)
{
    std::vector<uint8_t> packet;

    insertMagic(packet);

    this->serializeData(packet, &clientId);

    // header
    MenuPacketType menuPacketType = MenuPacketType::ROOM_EDIT;
    this->serializeData(packet, &menuPacketType);
    this->serializeData(packet, &editType);

    // body
    int id = room.getId();
    std::size_t maxPlayers = room.getMaxPlayers();
    std::size_t nbPlayers = room.getNbPlayers();

    this->serializeData(packet, &id);
    this->serializeData(packet, &maxPlayers);
    this->serializeData(packet, &nbPlayers);

    insertMagic(packet);

    return this->convertToData(packet);
}

void MenuSerializer::deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms, std::size_t &roomCount)
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

_STORAGE_DATA MenuSerializer::serializeRoomAction(std::size_t clientId, std::size_t roomId, RoomAction action)
{
    std::vector<uint8_t> packet;

    insertMagic(packet);

    this->serializeData(packet, &clientId);

    // header
    MenuPacketType menuPacketType = MenuPacketType::ROOM_ACTION;
    this->serializeData(packet, &menuPacketType);
    this->serializeData(packet, &action);

    // body
    this->serializeData(packet, &roomId);

    insertMagic(packet);

    return this->convertToData(packet);
}

void MenuSerializer::deserializeEvent(std::vector<uint8_t> packet)
{
    std::size_t adv = MAGIC_SIZE + sizeof(MenuPacketType);

    // TODO
}
