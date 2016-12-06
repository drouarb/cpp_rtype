//
// Created by celeriy on 28/11/16.
//


#include "listener/ClientListenerMoveEntity.hh"
using namespace client;
ClientListenerMoveEntity::ClientListenerMoveEntity(GameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::MOVE_ENTITY)
{

}

ClientListenerMoveEntity::~ClientListenerMoveEntity()
{

}

void ClientListenerMoveEntity::notify(const network::packet::PacketMoveEntity *packet)
{

}
