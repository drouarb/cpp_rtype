//
// Created by drouar_b on 12/6/16.
//

#include <cstring>
#include <stdexcept>
#include <unistd.h>
#include <network/packet/PacketSyn.hh>
#include <network/packet/PacketSynAck.hh>
#include <network/packet/PacketAck.hh>
#include <network/packet/PacketPing.hh>
#include <network/packet/PacketPong.hh>
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

    bool found;
    struct sockaddr_in recvSocket;
    socklen_t recvSocketLen = sizeof(recvSocket);
    std::vector<uint8_t> buffer(SOCKET_BUFFER);

    pollfd.fd = mainSocketFd;
    pollfd.events = POLLIN;
    pollfd.revents = 0;
    status = CONNECTED;

    while (status == CONNECTED) {
        int ret = ::poll(&pollfd, 1, POLL_TIMEOUT);
        if (ret) {
            recvfrom(mainSocketFd, buffer.data(), SOCKET_BUFFER, 0, (struct sockaddr *) &recvSocket, &recvSocketLen);
            found = false;
            for (auto it = clients.begin(); it != clients.end(); it++) {
                if (getClientId((*it).client) == getClientId(recvSocket)) {
                    found = true;
                    (*it).sw.set();
                    if ((*it).status == CONNECTED)
                        handleServerData(buffer, (*it));
                    if ((*it).status == CONNECTING)
                        if (!handleServerHandshake(buffer, (*it), ACK))
                            clients.erase(it);
                    break;
                }
            }
            if (!found) {
                clients.emplace_back();
                clients.back().status = CONNECTING;
                if (!handleServerHandshake(buffer, clients.back(), SYNACK))
                    clients.pop_back();
            }
        }
        handleServerTimeout();
    }
    status = DISCONNECTED;
}

void network::socket::UnixUDPSocket::handleServerData(std::vector<uint8_t> &data, struct s_UDPClient &client) {
    try {
        std::vector<uint8_t> buff;
        packet::PacketPing packetPing;
        packet::PacketPong packetPong;

        packetPing.deserialize(&data);
        packetPong.serialize(&buff);
        send(buff, getClientId(client.client));
    } catch (std::exception e) {
        for (auto &l : dataListeners) {
            l->notify(getClientId(client.client), &data);
        }
    }
}

bool network::socket::UnixUDPSocket::handleServerHandshake(std::vector<uint8_t> &data, struct s_UDPClient &client,
                                                           e_handshakeState state) {
    if (state == SYNACK) {
        try {
            std::vector<uint8_t> buff;
            packet::PacketSyn packetSyn;
            packet::PacketSynAck packetSynAck;

            packetSyn.deserialize(&data);

            client.ack = (uint16_t)rand();
            packetSynAck.setSyn(packetSyn.getSyn());
            packetSynAck.setAck(client.ack);

            packetSynAck.serialize(&buff);
            send(buff, getClientId(client.client));
        } catch (std::exception e) {
            return false;
        }
    } else {
        try {
            packet::PacketAck packetAck;
            packetAck.deserialize(&data);

            if (packetAck.getAck() != client.ack)
                return false;
            else {
                for (auto &l : connectionListeners) {
                    l->notify(getClientId(client.client));
                }
            }
        } catch (std::exception e) {
            return false;
        }
    }
    return true;
}

void network::socket::UnixUDPSocket::handleServerTimeout() {
    std::vector<uint8_t> buff;
    packet::PacketPing packetPing;
    std::list<std::list<struct s_UDPClient>::iterator> to_disconnect;

    packetPing.serialize(&buff);
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if ((*it).status == CONNECTED) {
            if ((*it).sw.elapsedMs() > (*it).npings * PING_TIME) {
                if ((*it).npings < MAX_PINGS) {
                    send(buff, getClientId((*it).client));
                } else {
                    to_disconnect.push_back(it);
                }
            }
        } else {
            if ((*it).sw.elapsedMs() > MAX_PINGS * PING_TIME) {
                to_disconnect.push_back(it);
            }
        }
    }
    for (auto &it : to_disconnect) {
        if ((*it).status == CONNECTED)
            for (auto &l : disconnectionListeners)
                l->notify(getClientId((*it).client));
        clients.erase(it);
    }
}

void network::socket::UnixUDPSocket::clientPoll() {
    //TODO Handshake
    while (status == CONNECTED) {
        //TODO client stuffs
    }
}

void network::socket::UnixUDPSocket::broadcast(const std::vector<uint8_t> &data) {
    if (status != CONNECTED)
        throw new std::runtime_error("Can't send if socket isn't running");
    if (type == SERVER) {
        for (auto &client : clients) {
            if (client.status == CONNECTED) {
                sendto(mainSocketFd, data.data(), data.size(), 0, (sockaddr *) &client.client, sizeof(client.client));
            }
        }
    } else {
        sendto(mainSocketFd, data.data(), data.size(), 0, (sockaddr *) &mainSocket, sizeof(&mainSocket));
    }
}

void network::socket::UnixUDPSocket::send(const std::vector<uint8_t> &data, unsigned long dest) {
    if (status != CONNECTED)
        throw new std::runtime_error("Can't send if socket isn't running");
    if (type == SERVER) {
        for (auto &client : clients) {
            if (getClientId(client.client) == dest && client.status == CONNECTED) {
                sendto(mainSocketFd, data.data(), data.size(), 0, (sockaddr *) &client.client, sizeof(client.client));
                return;
            }
        }
    } else {
        sendto(mainSocketFd, data.data(), data.size(), 0, (sockaddr *) &mainSocket, sizeof(&mainSocket));
    }
}

unsigned long network::socket::UnixUDPSocket::getClientId(const struct sockaddr_in &client) {
    unsigned long id = client.sin_addr.s_addr;
    id <<= 16;
    id |= client.sin_port;
    return id;
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
