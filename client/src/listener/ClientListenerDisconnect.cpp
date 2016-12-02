//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerDisconnect.hh"

using namespace client;
ClientListenerDisconnect::ClientListenerDisconnect(IGameClient *gameClient) :  gameclient(gameClient),  APacketListener(network::packet::DISCONNECT)
{
}

ClientListenerDisconnect::~ClientListenerDisconnect()
{

}

void ClientListenerDisconnect::notify(const network::packet::PacketDisconnect *packet)
{

}
