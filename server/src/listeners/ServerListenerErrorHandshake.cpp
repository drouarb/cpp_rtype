//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerErrorHandshake.hh"

server::ServerListenerErrorHandshake::ServerListenerErrorHandshake() : APacketListener(network::packet::ERROR_HANDSHAKE) {}

void server::ServerListenerErrorHandshake::notify(const network::packet::PacketErrorHandshake *packet) {

}
