//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerSpawnEntity.hh"
using namespace client;
ClientListenerSpawnEntity::ClientListenerSpawnEntity(GameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::SPAWN_ENTITY)
{

}

ClientListenerSpawnEntity::~ClientListenerSpawnEntity()
{

}

void ClientListenerSpawnEntity::notify(const network::packet::PacketSpawnEntity *packet)
{

}
