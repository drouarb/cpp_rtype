//
// Created by drouar_b on 12/6/16.
//

#include "network/socket/UnixUDPSocket.hh"

bool network::socket::UnixUDPSocket::run() {
    return false;
}

void network::socket::UnixUDPSocket::poll() {

}

bool network::socket::UnixUDPSocket::stop() {
    return false;
}

void network::socket::UnixUDPSocket::broadcast(std::vector<uint8_t> *data) {

}

void network::socket::UnixUDPSocket::send(std::vector<uint8_t> *data, int dest) {

}

void
network::socket::UnixUDPSocket::registerConnectionListener(network::listener::ISocketConnectionListener *listener) {

}

void
network::socket::UnixUDPSocket::unregisterConnectionListener(network::listener::ISocketConnectionListener *listener) {

}

void network::socket::UnixUDPSocket::registerDisconnectionListener(
        network::listener::ISocketDisconnectionListener *listener) {

}

void network::socket::UnixUDPSocket::unregisterDisconnectionListener(
        network::listener::ISocketDisconnectionListener *listener) {

}

void network::socket::UnixUDPSocket::registerDataListener(network::listener::ISocketDataListener *listener) {

}

void network::socket::UnixUDPSocket::unregisterDataListener(network::listener::ISocketDataListener *listener) {

}
