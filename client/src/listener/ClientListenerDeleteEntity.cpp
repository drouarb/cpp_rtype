//
// Created by celeriy on 28/11/16.
//

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

}
