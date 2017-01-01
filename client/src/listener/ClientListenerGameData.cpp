//
// Created by celeriy on 01/01/17.
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
    networkManager->receiveGameData(packet->getAudio(), packet->getBackground());
}

