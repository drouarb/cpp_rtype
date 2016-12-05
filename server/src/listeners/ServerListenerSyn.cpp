//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerSyn.hh"

server::ServerListenerSyn::ServerListenerSyn() : APacketListener(network::packet::SYN) {

}

void server::ServerListenerSyn::notify(const network::packet::PacketSyn *packet) {

}
