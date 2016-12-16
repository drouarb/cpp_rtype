//
// Created by celeriy on 16/12/16.
//

#include "listener/ClientListenerGameData.hh"
using namespace client;
ClientListenerGameData::ClientListenerGameData(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::GAME_DATA)
{

}

ClientListenerGameData::~ClientListenerGameData()
{

}

void ClientListenerGameData::notify(const network::packet::PacketGameData *packet)
{
    networkManager->receiveGameData(packet->getTick(), packet->getTime());
}
