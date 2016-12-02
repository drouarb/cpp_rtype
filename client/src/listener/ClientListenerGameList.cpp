//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerGameList.hh"
using namespace client;
ClientListenerGameList::ClientListenerGameList(IGameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::GAME_LIST)
{

}

ClientListenerGameList::~ClientListenerGameList()
{

}
void ClientListenerGameList::notify(const network::packet::PacketGameList *packet)
{

}
