//
// Created by celeriy on 28/11/16.
//

#include <iostream>
#include "listener/ClientListenerDeleteEntity.hh"
using namespace client;
ClientListenerDeleteEntity::ClientListenerDeleteEntity(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::DELETE_ENTITY)
{

}

ClientListenerDeleteEntity::~ClientListenerDeleteEntity()
{

}

void ClientListenerDeleteEntity::notify(const network::packet::PacketDeleteEntity *packet)
{
  //  std::cout << "receive delete entity id : " << packet->getEntity() << std::endl;
    this->networkManager->receiveDeleteEntity(packet->getTick(), packet->getEventId(), packet->getEntityId());
}
