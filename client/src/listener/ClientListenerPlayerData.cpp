//
// Created by celeriy on 19/12/16.
//

#include "listener/ClientListenerPlayerData.hh"
#include "listener/ClientListenerPlayerData.hh"
using namespace client;

ClientListenerPlayerData::ClientListenerPlayerData(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::PLAYER_DATA)
{

}

ClientListenerPlayerData::~ClientListenerPlayerData()
{

}

void ClientListenerPlayerData::notify(const network::packet::PacketPlayerData *packet)
{
    networkManager->receivePlayerData(packet->getPlayerId(),packet->getNbAttack());
}