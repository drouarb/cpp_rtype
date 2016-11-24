//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketQuit.hh"

network::packet::PacketQuit::~PacketQuit()
{

}

network::packet::PacketQuit::PacketQuit() :
        APacket
                (
                        QUIT, {}
                )
{}
