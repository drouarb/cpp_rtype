//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerGameList.hh"
using namespace client;
ClientListenerGameList::ClientListenerGameList(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::GAME_LIST)
{

}

ClientListenerGameList::~ClientListenerGameList()
{

}
void ClientListenerGameList::notify(const network::packet::PacketGameList *packet)
{
    networkManager->receiveGameList(packet->getGameList());
}
