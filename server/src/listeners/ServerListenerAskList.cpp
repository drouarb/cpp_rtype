//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerAskList.hh"

server::ServerListenerAskList::ServerListenerAskList() : APacketListener(network::packet::ASK_LIST) {

}

void server::ServerListenerAskList::notify(const network::packet::PacketAskList *packet) {

}
