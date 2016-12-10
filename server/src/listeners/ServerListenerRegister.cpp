//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerRegister.hh"

server::ServerListenerRegister::ServerListenerRegister() : APacketListener(network::packet::REGISTER) {

}

void server::ServerListenerRegister::notify(const network::packet::PacketRegister *packet) {
    this->listenerHandler->clientRegister(packet->getSource(), packet->getMessage());
}

server::ServerListenerRegister::ServerListenerRegister(server::IListenerHandler *iListenerHandler) : listenerHandler(iListenerHandler), APacketListener(network::packet::REGISTER) {}
