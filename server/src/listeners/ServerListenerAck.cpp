//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerAck.hh"

server::ServerListenerAck::ServerListenerAck() : APacketListener(network::packet::ACK) {

}

void server::ServerListenerAck::notify(const network::packet::PacketAck *packet) {

}
