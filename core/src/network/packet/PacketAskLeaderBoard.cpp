//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketAskLeaderBoard.hh"


network::packet::PacketAskLeaderBoard::~PacketAskLeaderBoard()
{

}

network::packet::PacketAskLeaderBoard::PacketAskLeaderBoard() :
        APacket
                (
                        ASK_LEADERBOARD, {}
                )
{}
