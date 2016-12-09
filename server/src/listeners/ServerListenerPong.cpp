//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerPong.hh"

void server::ServerListenerPong::notify(const network::packet::PacketPong *packet) {

}

server::ServerListenerPong::ServerListenerPong(server::IListenerHandler *iListenerHandler) : listenerHandler(iListenerHandler), APacketListener(network::packet::PONG) {}
