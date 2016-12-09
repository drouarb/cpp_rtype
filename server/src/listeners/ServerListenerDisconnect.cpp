//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerDisconnect.hh"


void server::ServerListenerDisconnect::notify(const network::packet::PacketDisconnect *packet) {
    this->listenerHandler->clientDisconnect(packet->getSource());
}

server::ServerListenerDisconnect::ServerListenerDisconnect(server::IListenerHandler *iListenerHandler) : listenerHandler(
        iListenerHandler), APacketListener(network::packet::DISCONNECT) {}
