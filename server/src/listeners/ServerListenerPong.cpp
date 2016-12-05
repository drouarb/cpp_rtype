//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerPong.hh"

server::ServerListenerPong::ServerListenerPong() : APacketListener(network::packet::PONG) {

}

void server::ServerListenerPong::notify(const network::packet::PacketPong *packet) {

}
