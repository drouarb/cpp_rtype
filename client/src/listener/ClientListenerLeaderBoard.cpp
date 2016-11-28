//
// Created by celeriy on 28/11/16.
//

#include "listener/ClientListenerLeaderBoard.hh"

ClientListenerLeaderBoard::ClientListenerLeaderBoard(IGameClient *gameClient) : gameclient(gameClient), APacketListener(network::packet::LEADER_BOARD)
{

}

ClientListenerLeaderBoard::~ClientListenerLeaderBoard()
{

}

void ClientListenerLeaderBoard::notify(const network::packet::PacketLeaderBoard *packet)
{

}
