//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerLeaderBoard.hh"
using namespace client;
ClientListenerLeaderBoard::ClientListenerLeaderBoard(NetworkManager *networkManager) : networkManager(networkManager), APacketListener(network::packet::LEADER_BOARD)
{

}

ClientListenerLeaderBoard::~ClientListenerLeaderBoard()
{

}

void ClientListenerLeaderBoard::notify(const network::packet::PacketLeaderBoard *packet)
{
    networkManager->receiveLeaderBoard(packet->getLeaderBoard());
}
