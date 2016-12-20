//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerAskLeaderboard.hh"

server::ServerListenerAskLeaderboard::ServerListenerAskLeaderboard() : APacketListener(network::packet::ASK_LEADERBOARD) {
    //TODO
}

void server::ServerListenerAskLeaderboard::notify(const network::packet::PacketAskLeaderBoard *packet) {

}
