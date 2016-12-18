//
// Created by greg on 05/12/2016.
//

#include <listeners/IListenerHandler.hh>
#include <listeners/ServerListenerAskList.hh>
#include "listeners/ServerListenerAskList.hh"

void server::ServerListenerAskList::notify(const network::packet::PacketAskList *packet) {
    this->iListenerHandler->askGame(packet->getSource());
}

server::ServerListenerAskList::ServerListenerAskList(IListenerHandler *iListenerHandler) : iListenerHandler(
        iListenerHandler), APacketListener(network::packet::ASK_LIST) {}
