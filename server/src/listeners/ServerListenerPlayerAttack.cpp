//
// Created by greg on 05/12/2016.
//

#include <iostream>
#include "listeners/ServerListenerPlayerAttack.hh"

server::ServerListenerPlayerAttack::ServerListenerPlayerAttack() : APacketListener(network::packet::PLAYER_ATTACK) {

}

void server::ServerListenerPlayerAttack::notify(const network::packet::PacketPlayerAttack *packet) {
    std::cout << "BEGIN" << std::endl;
    this->listenerHandler->clientPlayerAttack(packet->getSource(), packet->getAttackId(), packet->getTick());
    std::cout << "OK" << std::endl;
}

server::ServerListenerPlayerAttack::ServerListenerPlayerAttack(server::IListenerHandler *iListenerHandler) : APacketListener(network::packet::PLAYER_ATTACK), listenerHandler(iListenerHandler) {}
