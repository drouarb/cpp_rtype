//
// Created by celeriy on 01/01/17.
//

#include "listener/ClientListenerErrorGame.hh"


using namespace client;
ClientListenerErrorGame::ClientListenerErrorGame(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::ERROR_GAME)
{

}

ClientListenerErrorGame::~ClientListenerErrorGame()
{

}

void ClientListenerErrorGame::notify(const network::packet::PacketErrorGame *packet)
{
    networkManager->receiveErrorGame(packet->getMessage());
}
