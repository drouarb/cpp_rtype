//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerQuit.hh"

using namespace client;
ClientListenerQuit::ClientListenerQuit(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::QUIT)
{

}

ClientListenerQuit::~ClientListenerQuit()
{

}

void ClientListenerQuit::notify(const network::packet::PacketQuit *packet)
{

}
