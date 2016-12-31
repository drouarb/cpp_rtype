//
// Created by celeriy on 16/12/16.
//

#include <network/packet/IPacket.hh>
#include <iostream>
#include "listener/ClientListenerSynchronization.hh"
using namespace client;
ClientListenerSynchronization::ClientListenerSynchronization(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::SYNCHRONIZATION)
{

}

ClientListenerSynchronization::~ClientListenerSynchronization()
{

}

void ClientListenerSynchronization::notify(const network::packet::PacketSynchronization *packet)
{
    networkManager->receiveSynchronization(packet->getTick(), packet->getTime());
}
