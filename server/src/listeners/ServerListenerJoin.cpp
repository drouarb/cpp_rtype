//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerJoin.hh"


void server::ServerListenerJoin::notify(const network::packet::PacketJoin *packet) {
    this->listenerHandler->clientJoin(packet->getSource(), packet->getJoin());
}

server::ServerListenerJoin::ServerListenerJoin(server::IListenerHandler *iListenerHandler) : APacketListener(network::packet::JOIN), listenerHandler(iListenerHandler)
{ }
