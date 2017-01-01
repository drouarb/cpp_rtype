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
  std::cout << "synchro ==================== tick : " << packet->getTick() << " time : " << packet->getTime() << std::endl;
    networkManager->receiveSynchronization(packet->getTick(), packet->getTime());
}
