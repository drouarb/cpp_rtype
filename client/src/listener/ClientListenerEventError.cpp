//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerEventError.hh"

using namespace client;
ClientListenerEventError::ClientListenerEventError(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::EVENT_ERROR)
{

}

ClientListenerEventError::~ClientListenerEventError()
{

}

void ClientListenerEventError::notify(const network::packet::PacketEventError *packet)
{

}
