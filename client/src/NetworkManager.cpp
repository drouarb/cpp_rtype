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
    for (auto it = listeners.begin(); it != listeners.end(); it++)
        packetFactory->registerListener(*it);
}

void NetworkManager::receiveDeleteEntity(uint32_t tick, uint32_t eventId, uint16_t entityId) {
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

void
NetworkManager::receiveMoveEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t vecx, uint16_t vecy) {

}

void NetworkManager::receivePlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName) {

}

void NetworkManager::receiveQuit() {

}

void
NetworkManager::receiveSpawnEntity(uint32_t tick, uint32_t eventId, const std::string &spriteName, uint16_t entityId,
                                   uint16_t pos_x, uint16_t pos_y) {

}

void NetworkManager::receiveUpdateEntity(uint32_t tick, uint32_t eventId, uint16_t entityId, uint16_t hp) {

}

void NetworkManager::sendRegister(const std::string &name) {

    network::packet::PacketRegister packetRegister(name);
    packetFactory->send(packetRegister);
}

void NetworkManager::sendDisconnect() {
    network::packet::PacketDisconnect disconnect;
    packetFactory->send(disconnect);
}

void NetworkManager::sendAskList() {
    network::packet::PacketAskList askList;
    packetFactory->send(askList);
}

void NetworkManager::sendJoin(uint8_t roomId) {
    network::packet::PacketJoin join(roomId);
    packetFactory->send(join);
}

void NetworkManager::sendQuit() {
    network::packet::PacketQuit quit;
    packetFactory->send(quit);
}

void NetworkManager::sendPlayerMove(uint32_t tick, uint16_t vect_x, uint16_t vect_y) {
    network::packet::PacketPlayerMove playerMove(tick, vect_x, vect_y);
    packetFactory->send(playerMove);
}

void NetworkManager::sendPlayerAttack(int32_t tick, uint8_t attackId) {
    network::packet::PacketPlayerAttack packetPlayerAttack(tick, attackId);
    packetFactory->send(packetPlayerAttack);
}

