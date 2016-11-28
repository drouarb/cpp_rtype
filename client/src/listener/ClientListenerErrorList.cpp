//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerErrorList.hh"

ClientListenerErrorList::ClientListenerErrorList(IGameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::ERROR_LIST)
{

}

ClientListenerErrorList::~ClientListenerErrorList()
{

}

void ClientListenerErrorList::notify(const network::packet::PacketErrorList *packet)
{

}
