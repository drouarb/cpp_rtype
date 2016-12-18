//
// Created by celeriy on 29/11/16.
//

#include <stdexcept>
#include <network/packet/PacketSyn.hh>
#include <listener/ClientListenerCancelEvent.hh>
#include <listener/ClientListenerDeleteEntity.hh>
#include <listener/ClientListenerDisconnect.hh>
#include <listener/ClientListenerErrorList.hh>
#include <listener/ClientListenerEventError.hh>
#include <listener/ClientListenerGameList.hh>
#include <listener/ClientListenerLeaderBoard.hh>
#include <listener/ClientListenerMoveEntity.hh>
#include <listener/ClientListenerPlaySound.hh>
#include <listener/ClientListenerQuit.hh>
#include <listener/ClientListenerSpawnEntity.hh>
#include <listener/ClientListenerUpdateEntity.hh>
#include <iostream>
#include <network/packet/PacketAck.hh>
#include <network/packet/PacketRegister.hh>
#include <network/packet/PacketAskList.hh>
#include <network/packet/PacketJoin.hh>
#include <network/packet/PacketPlayerMove.hh>
#include <network/packet/PacketPlayerAttack.hh>
#include <listener/ClientListenerGameData.hh>
#include "NetworkManager.hh"

using namespace client;

NetworkManager::~NetworkManager()
{
    delete(packetFactory);
}

NetworkManager::NetworkManager(const std::string &ip, unsigned short port, GameClient *gameclient) : gameClient(gameclient)
{
    try
    {
        this->packetFactory =  new network::PacketFactory(ip, port);
    }
    catch (std::runtime_error & e)
    {
        this->packetFactory = nullptr;
        std::cerr << e.what() << std::endl;
        throw (std::runtime_error("netWorkManager failed to instance"));
    }
}

network::PacketFactory *NetworkManager::getPacketFactory() const
{
    return packetFactory;
}

bool NetworkManager::startPacketFactory()
{
    try {
        if (packetFactory == nullptr)
	  return false;
        packetFactory->run();
    }
    catch (std::exception & e)
    {
        throw (new std::runtime_error(e.what()));
    }
    return true;
}

void NetworkManager::addListenerToPacketFactory()
{
    listeners.push_back(new client::ClientListenerCancelEvent(this));
    listeners.push_back(new client::ClientListenerDeleteEntity(this));
    listeners.push_back(new client::ClientListenerDisconnect(this));
    listeners.push_back(new client::ClientListenerErrorList(this));
    listeners.push_back(new client::ClientListenerEventError(this));
    listeners.push_back(new client::ClientListenerGameList(this));
    listeners.push_back(new client::ClientListenerLeaderBoard(this));
    listeners.push_back(new client::ClientListenerMoveEntity(this));
    listeners.push_back(new client::ClientListenerPlaySound(this));
    listeners.push_back(new client::ClientListenerQuit(this));
    listeners.push_back(new client::ClientListenerSpawnEntity(this));
    listeners.push_back(new client::ClientListenerUpdateEntity(this));
    listeners.push_back(new client::ClientListenerGameData(this));
    for (auto it = listeners.begin(); it != listeners.end(); it++)
        packetFactory->registerListener(*it);
}

void NetworkManager::receiveDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId) {
    gameClient->manageDeleteEntity(tick, eventId, entityId);
}

void NetworkManager::receiveDisconnect() {
}

void NetworkManager::receiveCancelEvent(uint32_t eventId) {

}

void NetworkManager::receiveErrorList(const std::string &message) {

}

void NetworkManager::receiveEventError(const std::string &message) {

}

void NetworkManager::receiveGameList(const std::vector<std::pair<uint8_t, uint16_t >> GameList) {

}

void NetworkManager::receiveLeaderBoard(std::vector<std::pair<uint32_t, std::string>> LeaderBoard) {

}

void NetworkManager::receiveSyncro(uint32_t tick, int64_t time)
{
}

void NetworkManager::receivePlayerData(uint16_t playerId, uint8_t nbAttackPlayer)
{
}

void
NetworkManager::receiveMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t vecx, int16_t vecy,
                                  int16_t posx, int16_t posy) {
  gameClient->manageMoveEntity(tick , eventId, entityId, vecx, vecy, posx, posy);
}

void NetworkManager::receivePlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName) {

}

void NetworkManager::receiveQuit() {

}

void
NetworkManager::receiveSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint16_t entityId, int16_t pos_x,
                                   int16_t pos_y, int16_t hp) {
    gameClient->manageSpawnEntity(tick, eventId, spriteName, entityId, pos_x, pos_y, hp);

}

void NetworkManager::receiveUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, int16_t hp) {
    gameClient->manageUpdateEntity(tick, eventId, entityId, hp);
}

void NetworkManager::sendRegister(const std::string &name) {

    network::packet::PacketRegister packetRegister(name);
    packetFactory->broadcast(packetRegister);
}

void NetworkManager::sendDisconnect() {
    network::packet::PacketDisconnect disconnect;
    packetFactory->broadcast(disconnect);
}

void NetworkManager::sendAskList() {
    network::packet::PacketAskList askList;
    packetFactory->broadcast(askList);
}

void NetworkManager::sendJoin(uint8_t roomId) {
    network::packet::PacketJoin join(roomId);
    packetFactory->broadcast(join);
}

void NetworkManager::sendQuit() {
    network::packet::PacketQuit quit;
    packetFactory->broadcast(quit);
}

void NetworkManager::sendPlayerMove(uint32_t tick, int16_t vect_x, int16_t vect_y, int16_t pos_x, int16_t pos_y) {
    network::packet::PacketPlayerMove playerMove(tick, vect_x, vect_y, pos_x, pos_y);
    packetFactory->broadcast(playerMove);
}

void NetworkManager::sendPlayerAttack(int32_t tick, uint8_t attackId) {
    network::packet::PacketPlayerAttack packetPlayerAttack(tick, attackId);
    packetFactory->broadcast(packetPlayerAttack);
}

void NetworkManager::receiveGameData() {
}

