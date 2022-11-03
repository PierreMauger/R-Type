#include "Engine/Network/MenuSerializer.hpp"

using namespace eng;

MenuSerializer::MenuSerializer()
{
}

std::vector<Room>::iterator MenuSerializer::getRoom(std::vector<Room> rooms, std::size_t id)
{
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->getId() == id) {
            rooms.erase(it);
            return it;
        }
    }
    throw std::runtime_error("[ERROR] Room not found");
}

void MenuSerializer::editRoom(CrudType crudType, std::vector<Room> &rooms, std::size_t id, std::size_t maxPlayers, std::size_t nbPlayers)
{
    if (crudType == CrudType::CREATE) {
        rooms.push_back(Room(id, maxPlayers, nbPlayers));
        return;
    }

    auto roomIt = getRoom(rooms, id);

    if (crudType == CrudType::DESTROY) {
        rooms.erase(roomIt);
        return;
    }
    if (crudType == CrudType::UPDATE) {
        roomIt->setNbPlayers(nbPlayers);
        roomIt->setMaxPlayers(maxPlayers);
        return;
    }
    throw std::runtime_error("[ERROR] Invalid CRUD type");
}

_STORAGE_DATA MenuSerializer::serializeRoomEdit(CrudType editType, Room &room)
{
    std::vector<uint8_t> packet;

    insertMagic(packet);

    // header
    MenuPacketType menuPacketType = MenuPacketType::ROOM_EDIT;
    this->serializeData(packet, &menuPacketType);
    this->serializeData(packet, &editType);

    // body
    std::size_t id = room.getId();
    std::size_t maxPlayers = room.getMaxPlayers();
    std::size_t nbPlayers = room.getNbPlayers();

    this->serializeData(packet, &id);
    this->serializeData(packet, &maxPlayers);
    this->serializeData(packet, &nbPlayers);

    insertMagic(packet);

    return this->convertToData(packet);
}

void MenuSerializer::deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms)
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

    this->editRoom(crudType, rooms, id, maxPlayers, nbPlayers);
}

_STORAGE_DATA MenuSerializer::serializeRoomAction(std::size_t id, RoomAction action)
{
    std::vector<uint8_t> packet;

    insertMagic(packet);

    // header
    MenuPacketType menuPacketType = MenuPacketType::ROOM_ACTION;
    this->serializeData(packet, &menuPacketType);
    this->serializeData(packet, &action);

    // body
    this->serializeData(packet, &id);

    insertMagic(packet);

    return this->convertToData(packet);
}

void MenuSerializer::deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms)
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
        roomIt->addPlayer();
        break;
    case RoomAction::LEAVE:
        roomIt->removePlayer();
        break;
    case RoomAction::READY:
        break;
    case RoomAction::UNREADY:
        break;
    default:
        break;
    }
}

void MenuSerializer::deserializeEvent()
{
}

void MenuSerializer::handlePacket(_STORAGE_DATA packet, std::vector<Room> &rooms)
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
        this->deserializeRoomEdit(packetVector, rooms);
        break;
    case MenuPacketType::ROOM_ACTION:
        this->deserializeRoomAction(packetVector, rooms);
        break;
    case MenuPacketType::EVENT:
        this->deserializeEvent();
        break;
    default:
        throw std::runtime_error("[ERROR] Invalid packet type");
    }
}
