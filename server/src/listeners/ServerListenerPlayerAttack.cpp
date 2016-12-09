//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerPlayerAttack.hh"

server::ServerListenerPlayerAttack::ServerListenerPlayerAttack() : APacketListener(network::packet::PLAYER_ATTACK) {

}

void server::ServerListenerPlayerAttack::notify(const network::packet::PacketPlayerAttack *packet) {

}

server::ServerListenerPlayerAttack::ServerListenerPlayerAttack(server::IListenerHandler *iListenerHandler) : APacketListener(network::packet::PLAYER_ATTACK), listenerHandler(iListenerHandler) {}
