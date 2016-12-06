//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketDisconnect.hh"

network::packet::PacketDisconnect::~PacketDisconnect()
{

}

network::packet::PacketDisconnect::PacketDisconnect() :
APacket
        (
                DISCONNECT, {}
        )
{}
