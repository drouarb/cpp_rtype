//
// Created by celeriy on 19/12/16.
//

#include <iostream>
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
    std::cout << "receive layer data : " << packet->getPlayerId() << std::endl;
    networkManager->receivePlayerData(packet->getPlayerId(),packet->getNbAttack());
}