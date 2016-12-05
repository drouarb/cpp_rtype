//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerDisconnect.hh"

server::ServerListenerDisconnect::ServerListenerDisconnect() : APacketListener(network::packet::DISCONNECT) {

}

void server::ServerListenerDisconnect::notify(const network::packet::PacketDisconnect *packet) {

}
