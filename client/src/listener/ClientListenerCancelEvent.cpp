//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerCancelEvent.hh"

using namespace client;
ClientListenerCancelEvent::ClientListenerCancelEvent(client::IGameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::CANCEL_EVENT)
{

}

ClientListenerCancelEvent::~ClientListenerCancelEvent()
{

}

void ClientListenerCancelEvent::notify(const network::packet::PacketCancelEvent *packet)
{

}
