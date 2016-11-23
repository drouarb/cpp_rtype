//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketAskList.hh"

network::packet::PacketAskList::~PacketAskList()
{

}

network::packet::PacketAskList::PacketAskList() :
        APacket(
                ASK_LIST,
                {
                }
        )
{}