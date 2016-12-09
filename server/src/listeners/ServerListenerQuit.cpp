//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerQuit.hh"

server::ServerListenerQuit::ServerListenerQuit() : APacketListener(network::packet::QUIT) {

}

void server::ServerListenerQuit::notify(const network::packet::PacketQuit *packet) {

}

server::ServerListenerQuit::ServerListenerQuit(server::IListenerHandler *iListenerHandler) : listenerHandler(iListenerHandler), APacketListener(network::packet::QUIT) {}
