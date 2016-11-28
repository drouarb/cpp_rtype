//
// Created by celeriy on 23/11/16.
//

#include <network/utils/NetworkVector.hh>
#include "network/packet/PacketLeaderBoard.hh"
network::packet::PacketLeaderBoard::PacketLeaderBoard(std::vector<std::pair<uint32_t, std::string>> LeaderBoard):
        APacket(
                LEADER_BOARD,
                {
                        new utils::NetworkVector(2, {
                                new utils::NetworkInteger(1),
                                new utils::NetworkString
                        })
                }
        )
{
    for (size_t i = 0; i < LeaderBoard.size(); i++) {
        SET_NETINT(GET_NETVEC(schema, 0)[i], 0, LeaderBoard[i].first);
        SET_NETSTR(GET_NETVEC(schema, 0)[i], 1, LeaderBoard[i].second);
    }
}

network::packet::PacketLeaderBoard::~PacketLeaderBoard()
{ }

std::vector<std::pair<uint32_t, std::string>> network::packet::PacketLeaderBoard::getLeaderBoard() const {
    std::vector<std::pair<uint32_t, std::string>> list;

    for (size_t i = 0; i < GET_NETVEC(schema, 0).size(); i++) {
        list.push_back({
                               GET_NETINT(GET_NETVEC(schema, 0)[i], 0),
                               GET_NETSTR(GET_NETVEC(schema, 0)[i], 1)
                       });
    }
    return (list);
}