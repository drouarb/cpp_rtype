//
// Created by celeriy on 28/11/16.
//

#include <iostream>
#include "listener/ClientListenerSpawnEntity.hh"
using namespace client;
ClientListenerSpawnEntity::ClientListenerSpawnEntity(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::SPAWN_ENTITY)
{

}

ClientListenerSpawnEntity::~ClientListenerSpawnEntity()
{

}

void ClientListenerSpawnEntity::notify(const network::packet::PacketSpawnEntity *packet)
{
    std::cout << "receive spawn entity" << std::endl;
    networkManager->receiveSpawnEntity(packet->getTick(), packet->getEventId(), packet->getSpriteName(),
                                       packet->getEntityId(), packet->getPosX(), packet->getPosY(), packet->getHp());
}
