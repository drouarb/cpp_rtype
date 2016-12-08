//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerErrorList.hh"
using namespace client;
ClientListenerErrorList::ClientListenerErrorList(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::ERROR_LIST)
{

}

ClientListenerErrorList::~ClientListenerErrorList()
{

}

void ClientListenerErrorList::notify(const network::packet::PacketErrorList *packet)
{

}
