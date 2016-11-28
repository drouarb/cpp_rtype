//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerUpdateEntity.hh"


ClientListenerUpdateEntity::ClientListenerUpdateEntity(IGameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::UPDATE_ENTITY)
{

}

ClientListenerUpdateEntity::~ClientListenerUpdateEntity()
{

}

void ClientListenerUpdateEntity::notify(const network::packet::PacketUpdateEntity *packet)
{

}
