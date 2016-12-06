//
// Created by drouar_b on 12/6/16.
//

#include <cstring>
#include <stdexcept>
#include <unistd.h>
#include "network/socket/UnixUDPSocket.hh"

network::socket::UnixUDPSocket::UnixUDPSocket(unsigned short port) : type(network::socket::ISocket::SERVER),
                                                                     status(DISCONNECTED) {
    memset(&mainSocket, 0, sizeof(mainSocket));
    mainSocket.sin_family = AF_INET;
    mainSocket.sin_port = htons(port);
    mainSocket.sin_addr.s_addr = htonl(INADDR_ANY);
}

network::socket::UnixUDPSocket::UnixUDPSocket(const std::string &address, unsigned short port) : type(
        network::socket::ISocket::CLIENT),
                                                                                                 status(DISCONNECTED) {
    memset(&mainSocket, 0, sizeof(mainSocket));
    mainSocket.sin_family = AF_INET;
    mainSocket.sin_port = htons(port);
    if (inet_aton(address.c_str(), &mainSocket.sin_addr) == 0)
        throw new std::runtime_error("UnixUDPSocket Invalid ip");

}

bool network::socket::UnixUDPSocket::run() {
    //TODO thread poll
    return false;
}

bool network::socket::UnixUDPSocket::stop() {
    status = STOPPING;
    //TODO stop thread
    return false;
}

void network::socket::UnixUDPSocket::poll() {
    if (status != DISCONNECTED)
        throw new std::runtime_error("UnixUDPSocket Already running");
    status = CONNECTING;
    if (type == CLIENT)
        clientPoll();
    else
        serverPoll();
}

void network::socket::UnixUDPSocket::serverPoll() {
    if ((mainSocketFd = ::socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        status = DISCONNECTED;
        throw new std::runtime_error("UnixUDPSocket can't instantiate socket");
    }
    if (bind(mainSocketFd, (struct sockaddr *) &mainSocket, sizeof(mainSocket)) == -1) {
        close(mainSocketFd);
        status = DISCONNECTED;
        throw new std::runtime_error("UnixUDPSocket can't bind port");
    }

    status = CONNECTED;
    while (status == CONNECTED) {
        //TODO server stuffs
    }
    status = DISCONNECTED;
}

void network::socket::UnixUDPSocket::clientPoll() {
    //TODO Handshake
    while (status == CONNECTED) {
        //TODO client stuffs
    }
}

void network::socket::UnixUDPSocket::broadcast(std::vector<uint8_t> *data) {
    if (status != CONNECTED)
        throw new std::runtime_error("Can't send if socket isn't running");
    if (type == SERVER) {
        for (auto client : clients) {
            if (client.status == CONNECTED) {
                sendto(mainSocketFd, data->data(), data->size(), 0, (sockaddr *)&client.client, sizeof(client.client));
            }
        }
    } else {
        sendto(mainSocketFd, data->data(), data->size(), 0, (sockaddr *)&mainSocket, sizeof(&mainSocket));
    }
}

void network::socket::UnixUDPSocket::send(std::vector<uint8_t> *data, unsigned long dest) {
    if (status != CONNECTED)
        throw new std::runtime_error("Can't send if socket isn't running");
    //TODO Send data
}

void
network::socket::UnixUDPSocket::registerConnectionListener(network::listener::ISocketConnectionListener *listener) {
    connectionListeners.push_front(listener);
}

void
network::socket::UnixUDPSocket::unregisterConnectionListener(network::listener::ISocketConnectionListener *listener) {
    connectionListeners.remove(listener);
}

void network::socket::UnixUDPSocket::registerDisconnectionListener(
        network::listener::ISocketDisconnectionListener *listener) {
    disconnectionListeners.push_front(listener);
}

void network::socket::UnixUDPSocket::unregisterDisconnectionListener(
        network::listener::ISocketDisconnectionListener *listener) {
    disconnectionListeners.remove(listener);
}

void network::socket::UnixUDPSocket::registerDataListener(network::listener::ISocketDataListener *listener) {
    dataListeners.push_front(listener);
}

void network::socket::UnixUDPSocket::unregisterDataListener(network::listener::ISocketDataListener *listener) {
    dataListeners.remove(listener);
}

network::socket::ISocket::e_socketType network::socket::UnixUDPSocket::getType() {
    return type;
}

network::socket::ISocket::e_socketStatus network::socket::UnixUDPSocket::getStatus() {
    return status;
}
