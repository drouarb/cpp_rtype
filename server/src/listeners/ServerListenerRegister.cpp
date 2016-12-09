//
// Created by greg on 05/12/2016.
//

#include "listeners/ServerListenerRegister.hh"

server::ServerListenerRegister::ServerListenerRegister() : APacketListener(network::packet::REGISTER) {

}

void server::ServerListenerRegister::notify(const network::packet::PacketRegister *packet) {
}

server::ServerListenerRegister::ServerListenerRegister(server::IListenerHandler *iListenerHandler) : IListenerHandler(
        IListenerHandler), APacketListener(network::packet::REGISTER) {}
