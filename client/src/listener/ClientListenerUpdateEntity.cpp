//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerUpdateEntity.hh"

using namespace client;
ClientListenerUpdateEntity::ClientListenerUpdateEntity(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::UPDATE_ENTITY)
{

}

ClientListenerUpdateEntity::~ClientListenerUpdateEntity()
{

}

void ClientListenerUpdateEntity::notify(const network::packet::PacketUpdateEntity *packet)
{
    networkManager->receiveUpdateEntity(packet->getTick(), packet->getEventId(), packet->getEntityId(), packet->getHp());
}
