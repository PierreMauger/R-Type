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

void MenuSerializer::editRoom(CrudType crudType, std::vector<Room> &rooms, int id, std::size_t maxPlayers, std::size_t nbPlayers, Client &client)
{
    auto roomIt = getRoom(rooms, id);

    if (roomIt == rooms.end()) {
        rooms.push_back(Room(id, maxPlayers, nbPlayers));
        rooms.back().addPlayer();
        client.setRoomId(id);
        // TODO set player
    }
    if (crudType == CrudType::UPDATE) {
        roomIt->setNbPlayers(nbPlayers);
        roomIt->setMaxPlayers(maxPlayers);
        return;
    }
    if (crudType == CrudType::DESTROY) {
        rooms.erase(roomIt);
        // TODO delete all clients in the room
        return;
    }
    throw std::runtime_error("[ERROR] Invalid CRUD type");
}

void MenuSerializer::handlePacket(_STORAGE_DATA packet, std::vector<Room> &rooms, Client &client, std::size_t &roomCount)
{
    std::size_t adv = 0;
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    MenuPacketType type;

    if (!this->checkMagic(packetVector, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    // skip id
    adv += (MAGIC_SIZE + sizeof(std::size_t));
    this->deserializeData<MenuPacketType>(packetVector, adv, &type);

    switch (type) {
    case MenuPacketType::ROOM_EDIT:
        this->deserializeRoomEdit(packetVector, rooms, roomCount, client);
        break;
    case MenuPacketType::ROOM_ACTION:
        this->deserializeRoomAction(packetVector, rooms, client);
        break;
    default:
        throw std::runtime_error("[ERROR] Invalid packet type");
    }
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
    int id = room.getId();
    std::size_t maxPlayers = room.getMaxPlayers();
    std::size_t nbPlayers = room.getNbPlayers();

    this->serializeData(packet, &id);
    this->serializeData(packet, &maxPlayers);
    this->serializeData(packet, &nbPlayers);

    insertMagic(packet);

    return this->convertToData(packet);
}

void MenuSerializer::deserializeRoomEdit(std::vector<uint8_t> packet, std::vector<Room> &rooms, std::size_t &roomCount, Client &client)
{
    std::size_t adv = MAGIC_SIZE + sizeof(std::size_t) + sizeof(MenuPacketType);
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
    this->editRoom(crudType, rooms, id, maxPlayers, nbPlayers, client);
}

void MenuSerializer::deserializeRoomAction(std::vector<uint8_t> packet, std::vector<Room> &rooms, Client &client)
{
    std::size_t adv = MAGIC_SIZE + sizeof(std::size_t) + sizeof(MenuPacketType);
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

_STORAGE_DATA MenuSerializer::serializeEvent(MenuEvent event)
{
    std::vector<uint8_t> packet;

    insertMagic(packet);

    // header
    MenuPacketType menuPacketType = MenuPacketType::EVENT;
    this->serializeData(packet, &menuPacketType);
    this->serializeData(packet, &event);

    insertMagic(packet);

    return this->convertToData(packet);
}

std::size_t MenuSerializer::getClientId(_STORAGE_DATA packet)
{
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    std::size_t adv = MAGIC_SIZE;
    std::size_t id;

    this->deserializeData(packetVector, adv, &id);
    return id;
}
