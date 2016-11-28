//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerCancelEvent.hh"


ClientListenerCancelEvent::ClientListenerCancelEvent(IGameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::CANCEL_EVENT)
{

}

ClientListenerCancelEvent::~ClientListenerCancelEvent()
{

}

void ClientListenerCancelEvent::notify(const network::packet::PacketCancelEvent *packet)
{

}
