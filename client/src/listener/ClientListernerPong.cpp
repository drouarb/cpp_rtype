//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListernerPong.hh"

using namespace client;
ClientListenerPong::ClientListenerPong(GameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::PONG)
{

}

ClientListenerPong::~ClientListenerPong()
{

}

void ClientListenerPong::notify(const network::packet::PacketPong *packet)
{

}
