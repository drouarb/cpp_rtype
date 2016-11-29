//
// Created by drouar_b on 11/29/16.
//

#include "network/PacketFactory.hh"

network::PacketFactory::PacketFactory(short port) {
    //SERVER
}

network::PacketFactory::PacketFactory(const std::string &address, short port) {
    //CLIENT
}

network::PacketFactory::~PacketFactory() {

}

void network::PacketFactory::run() {
    //non-threaded
}

void network::PacketFactory::poll() {
    //Threaded run
}

void network::PacketFactory::send(const network::packet::IPacket &packet) {
    //TODO BROADCAST PACKET
}

void network::PacketFactory::send(const network::packet::IPacket &packet, int fd) {
    //TODO SEND PACKET
}

void network::PacketFactory::registerConnectionListener(network::listener::ISocketConnectionListener *listener) {
    //TODO REGISTER LISTENER TO SOCKET
}

void network::PacketFactory::unregisterConnectionListener(network::listener::ISocketConnectionListener *listener) {
    //TODO REMOVE LISTENER FROM SOCKET
}

void network::PacketFactory::registerListener(network::listener::IPacketListener *listener) {
    //Register packet listener
}

void network::PacketFactory::unregisterListener(network::listener::IPacketListener *listener) {
    //Remove
}
