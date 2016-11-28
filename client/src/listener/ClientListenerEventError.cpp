//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerEventError.hh"


ClientListenerEventError::ClientListenerEventError(IGameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::EVENT_ERROR)
{

}

ClientListenerEventError::~ClientListenerEventError()
{

}

void ClientListenerEventError::notify(const network::packet::PacketEventError *packet)
{

}
