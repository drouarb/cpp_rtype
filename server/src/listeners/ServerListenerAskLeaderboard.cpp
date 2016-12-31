//
// Created by greg on 05/12/2016.
//

#include <listeners/IListenerHandler.hh>
#include <network/packet/IPacket.hh>
#include "listeners/ServerListenerAskLeaderboard.hh"

server::ServerListenerAskLeaderboard::ServerListenerAskLeaderboard(server::IListenerHandler *handler)
        : APacketListener(network::packet::ASK_LEADERBOARD), handler(handler) {
}

void server::ServerListenerAskLeaderboard::notify(const network::packet::PacketAskLeaderBoard *packet) {
    this->handler->askLeaderBoard(packet->getSource());
}
