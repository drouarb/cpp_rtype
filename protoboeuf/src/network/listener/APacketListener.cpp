//
// Created by drouar_b on 11/7/16.
//

#include "network/listener/APacketListener.hh"

network::listener::APacketListener::APacketListener(network::packet::PacketId id):
        packetId(id)
{ }

network::listener::APacketListener::~APacketListener()
{ }

network::packet::PacketId network::listener::APacketListener::getPacketId() const {
    return packetId;
}