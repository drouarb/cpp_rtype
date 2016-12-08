//
// Created by celeriy on 28/11/16.
//


#include "listener/ClientListenerMoveEntity.hh"
using namespace client;
ClientListenerMoveEntity::ClientListenerMoveEntity(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::MOVE_ENTITY)
{

}

ClientListenerMoveEntity::~ClientListenerMoveEntity()
{

}

void ClientListenerMoveEntity::notify(const network::packet::PacketMoveEntity *packet)
{
    networkManager->receiveMoveEntity(packet->getTick(), packet->getEventId(), packet->getEntityId(), packet->getVecX(), packet->getVecY());
}
