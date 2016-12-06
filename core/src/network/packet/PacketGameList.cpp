//
// Created by celeriy on 23/11/16.
//

#include <network/utils/NetworkVector.hh>
#include "network/packet/PacketGameList.hh"


network::packet::PacketGameList::PacketGameList(std::vector<std::pair<uint8_t, uint16_t>> GameList):
        APacket(
                GAME_LIST,
                {
                        new utils::NetworkVector(2, {
                                new utils::NetworkInteger(1),
                                new utils::NetworkInteger(2)
                        })
                }
        )
{
    for (size_t i = 0; i < GameList.size(); i++) {
        SET_NETINT(GET_NETVEC(schema, 0)[i], 0, GameList[i].first);
        SET_NETINT(GET_NETVEC(schema, 0)[i], 1, GameList[i].second);
    }
}

network::packet::PacketGameList::~PacketGameList()
{ }

std::vector<std::pair<uint8_t, uint16_t >> network::packet::PacketGameList::getGameList() const {
    std::vector<std::pair<uint8_t, uint16_t >> list;

    for (size_t i = 0; i < GET_NETVEC(schema, 0).size(); i++) {
        list.push_back({
                               GET_NETINT(GET_NETVEC(schema, 0)[i], 0),
                               GET_NETINT(GET_NETVEC(schema, 0)[i], 1)
                       });
    }
    return (list);
}
