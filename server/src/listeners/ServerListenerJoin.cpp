//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerJoin.hh"

server::ServerListenerJoin::ServerListenerJoin() : APacketListener(network::packet::JOIN) {

}

void server::ServerListenerJoin::notify(const network::packet::PacketJoin *packet) {

}
