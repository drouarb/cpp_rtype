//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerDisconnect.hh"


void server::ServerListenerDisconnect::notify(const network::packet::PacketDisconnect *packet) {
    this->IListenerHandler->clientDisconnect(packet->getSource());
}

server::ServerListenerDisconnect::ServerListenerDisconnect(server::IListenerHandler *iListenerHandler) : IListenerHandler(
        IListenerHandler), APacketListener(network::packet::DISCONNECT) {}
