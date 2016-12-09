//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerJoin.hh"


void server::ServerListenerJoin::notify(const network::packet::PacketJoin *packet) {

}

server::ServerListenerJoin::ServerListenerJoin(server::IListenerHandler *iListenerHandler) : APacketListener(network::packet::JOIN), IListenerHandler(IListenerHandler) {}
