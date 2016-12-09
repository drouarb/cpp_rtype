//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerPlayerMove.hh"

server::ServerListenerPlayerMove::ServerListenerPlayerMove() : APacketListener(network::packet::PLAYER_MOVE) {

}

void server::ServerListenerPlayerMove::notify(const network::packet::PacketPlayerMove *packet) {

}

server::ServerListenerPlayerMove::ServerListenerPlayerMove(server::IListenerHandler *iListenerHandler) : IListenerHandler(
        IListenerHandler), APacketListener(network::packet::PLAYER_MOVE) {}
