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
#include <network/packet/PacketDisconnect.hh>
#include "network/socket/UnixUDPSocket.hh"

network::socket::UnixUDPSocket::UnixUDPSocket(unsigned short port) : type(network::socket::ISocket::SERVER),
                                                                     status(DISCONNECTED), thread(NULL) {
    memset(&mainSocket, 0, sizeof(mainSocket));
    memset(&pollfd, 0, sizeof(pollfd));
    mainSocket.sin_family = AF_INET;
    mainSocket.sin_port = htons(port);
    mainSocket.sin_addr.s_addr = htonl(INADDR_ANY);
    pollfd.events = POLLIN;
}

network::socket::UnixUDPSocket::UnixUDPSocket(const std::string &address, unsigned short port) :
        type(network::socket::ISocket::CLIENT), status(DISCONNECTED), thread(NULL) {
    memset(&mainSocket, 0, sizeof(mainSocket));
    memset(&pollfd, 0, sizeof(pollfd));
    mainSocket.sin_family = AF_INET;
    mainSocket.sin_port = htons(port);
    pollfd.events = POLLIN;
    if (inet_aton(address.c_str(), &mainSocket.sin_addr) == 0)
        throw std::runtime_error("UnixUDPSocket Invalid ip");

}

network::socket::UnixUDPSocket::~UnixUDPSocket() {
    this->stop();
}

bool network::socket::UnixUDPSocket::run() {
    if (status != DISCONNECTED)
        throw std::runtime_error("UnixUDPSocket Already running");
    init();
    if (type == CLIENT)
        thread = new Thread<void (UnixUDPSocket::*)(), UnixUDPSocket*>(&UnixUDPSocket::clientPoll, this);
    else
        thread = new Thread<void (UnixUDPSocket::*)(), UnixUDPSocket*>(&UnixUDPSocket::serverPoll, this);
    return true;
}

bool network::socket::UnixUDPSocket::stop() {
    if (status == CONNECTING)
        while (status == CONNECTING);
    if (status == CONNECTED) {
        status = STOPPING;
        if (thread != NULL) {
            thread->join();
            delete(thread);
            thread = NULL;
        } else
            while (status != DISCONNECTED);
        return true;
    }
    return false;
}

void network::socket::UnixUDPSocket::init() {
    if (type == CLIENT)
        clientInit();
    else
        serverInit();
}

void network::socket::UnixUDPSocket::clientInit() {
    status = CONNECTING;

    if ((mainSocketFd = ::socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        status = DISCONNECTED;
        throw std::runtime_error("UnixUDPSocket can't instantiate socket");
    }

    clientHandshake();
    sw.set();
    npings = 0;
    status = CONNECTED;
}

void network::socket::UnixUDPSocket::serverInit() {
    status = CONNECTING;

    if ((mainSocketFd = ::socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        status = DISCONNECTED;
        throw std::runtime_error("UnixUDPSocket can't instantiate socket");
    }
    if (bind(mainSocketFd, (struct sockaddr *) &mainSocket, sizeof(mainSocket)) == -1) {
        close(mainSocketFd);
        status = DISCONNECTED;
        throw std::runtime_error("UnixUDPSocket can't bind port");
    }
    status = CONNECTED;
}

void network::socket::UnixUDPSocket::poll() {
    if (status != DISCONNECTED)
        throw std::runtime_error("UnixUDPSocket Already running");
    init();
    if (type == CLIENT)
        clientPoll();
    else
        serverPoll();
}

void network::socket::UnixUDPSocket::serverPoll() {
    bool found;
    struct sockaddr_in recvSocket;
    socklen_t recvSocketLen = sizeof(recvSocket);
    ssize_t size;
    std::vector<uint8_t> data;
    std::vector<uint8_t> buffer(SOCKET_BUFFER);

    while (status == CONNECTED) {
        pollfd.fd = mainSocketFd;
        if (::poll(&pollfd, 1, POLL_TIMEOUT) && status == CONNECTED) {
            size = recvfrom(mainSocketFd, buffer.data(), SOCKET_BUFFER, 0, (struct sockaddr *) &recvSocket, &recvSocketLen);
            data.assign(buffer.begin(), buffer.begin() + size);
            found = false;
            for (auto it = clients.begin(); it != clients.end(); it++) {
                if (getClientId((*it).client) == getClientId(recvSocket)) {
                    found = true;
                    (*it).sw.set();
                    (*it).npings = 0;
                    if ((*it).status == CONNECTED)
                        handleData(data, (*it).client);
                    if ((*it).status == CONNECTING)
                        if (!serverHandshake(data, (*it), ACK))
                            clients.erase(it);
                    break;
                }
            }
            if (!found) {
                clients.emplace_back();
                clients.back().status = CONNECTING;
                memcpy(&clients.back().client, &recvSocket, sizeof(recvSocket));
                if (!serverHandshake(data, clients.back(), SYNACK))
                    clients.pop_back();
            }
        }
        serverTimeout();
    }

    packet::PacketDisconnect packetDisconnect;
    buffer.resize(0);

    packetDisconnect.serialize(&buffer);
    for (auto &client : clients) {
        if (client.status == CONNECTED)
            sendto(mainSocketFd, buffer.data(), buffer.size(), 0, (sockaddr *) &client.client, sizeof(client.client));
    }
    clients.resize(0);
    close(mainSocketFd);
    status = DISCONNECTED;
}

bool network::socket::UnixUDPSocket::serverHandshake(std::vector<uint8_t> &data, struct s_UDPClient &client,
                                                     e_handshakeState state) {
    if (state == SYNACK) {
        try {
            std::vector<uint8_t> buff;
            packet::PacketSyn packetSyn;
            packet::PacketSynAck packetSynAck;

            packetSyn.deserialize(&data);

            client.ack = (uint16_t) rand();
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
                client.status = CONNECTED;
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

void network::socket::UnixUDPSocket::serverTimeout() {
    std::vector<uint8_t> buff;
    packet::PacketPing packetPing;
    std::list<std::list<struct s_UDPClient>::iterator> to_disconnect;

    packetPing.serialize(&buff);
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if ((*it).status == CONNECTED) {
            if ((*it).sw.elapsedMs() > ((*it).npings + 1) * PING_TIME) {
                if ((*it).npings < MAX_PINGS) {
                    send(buff, getClientId((*it).client));
                    (*it).npings++;
                } else {
                    to_disconnect.push_back(it);
                }
            }
        } else {
            if ((*it).sw.elapsedMs() > HANDSHAKE_TIMEOUT) {
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
    ssize_t size;
    std::vector<uint8_t> data;
    std::vector<uint8_t> buffer(SOCKET_BUFFER);

    pollfd.fd = mainSocketFd;
    while (status == CONNECTED) {
        if (::poll(&pollfd, 1, POLL_TIMEOUT) && status == CONNECTED) {
            size = recv(mainSocketFd, buffer.data(), buffer.size(), 0);
            data.assign(buffer.begin(), buffer.begin() + size);
            npings = 0;
            sw.set();
            handleData(data, mainSocket);
        }
        else
            clientTimeout();
    }
    if (status == STOPPING) {
        packet::PacketDisconnect packetDisconnect;
        buffer.resize(0);

        packetDisconnect.serialize(&buffer);
        sendto(mainSocketFd, buffer.data(), buffer.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));
        close(mainSocketFd);

        status = DISCONNECTED;
    }
}

void network::socket::UnixUDPSocket::clientHandshake() {
    std::vector<uint8_t> buff;
    packet::PacketSyn packetSyn;
    packet::PacketSynAck packetSynAck;
    packet::PacketAck packetAck;

    syn = (uint16_t) rand();
    packetSyn.setSyn(syn);
    packetSyn.serialize(&buff);
    sendto(mainSocketFd, buff.data(), buff.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));

    pollfd.fd = mainSocketFd;
    if (::poll(&pollfd, 1, HANDSHAKE_TIMEOUT) == 0)
        throw std::runtime_error("Client socket no handshake received");
    buff.resize(SOCKET_BUFFER);
    recv(mainSocketFd, buff.data(), SOCKET_BUFFER, 0);
    try {
        packetSynAck.deserialize(&buff);
    } catch (std::exception e) {
        throw std::runtime_error("Invalid SynAck response: bad packet");
    }
    if (packetSynAck.getSyn() != syn)
        throw std::runtime_error("Invalid SynAck response: bad syn");

    buff.resize(0);
    packetAck.setAck(packetSynAck.getAck());
    packetAck.serialize(&buff);
    sendto(mainSocketFd, buff.data(), buff.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));
}

void network::socket::UnixUDPSocket::clientTimeout() {
    if (sw.elapsedMs() > (npings + 1) * PING_TIME) {
        if (npings < MAX_PINGS) {
            std::vector<uint8_t> buff;
            packet::PacketPing packetPing;

            packetPing.serialize(&buff);
            broadcast(buff);
            npings++;
        } else
            clientDisconnect();
    }
}

void network::socket::UnixUDPSocket::handleData(const std::vector<uint8_t> &data, const struct sockaddr_in &client) {
    try {
        packet::PacketDisconnect packetDisconnect;

        packetDisconnect.deserialize(const_cast<std::vector<uint8_t> *>(&data));
        if (type == CLIENT)
            clientDisconnect();
        else
            serverDisconnect(client);
    } catch (std::exception e) {
        try {
            std::vector<uint8_t> buff;

            packet::PacketPing packetPing;
            packet::PacketPong packetPong;

            //TODO Const APacket Protoboeuf
            packetPing.deserialize(const_cast<std::vector<uint8_t> *>(&data));
            packetPong.serialize(&buff);
            send(buff, getClientId(client));
        } catch (std::exception e) {
            for (auto &l : dataListeners) {
                l->notify(getClientId(client), data);
            }
        }
    }
}

void network::socket::UnixUDPSocket::clientDisconnect() {
    status = DISCONNECTED;
    for (auto &l : disconnectionListeners) {
        l->notify(getClientId(mainSocket));
    }
    close(mainSocketFd);
}

void network::socket::UnixUDPSocket::serverDisconnect(const struct sockaddr_in &client) {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if (getClientId((*it).client) == getClientId(client)) {
            for (auto &l : disconnectionListeners)
                l->notify(getClientId((*it).client));
            clients.erase(it);
            return;
        }
    }
}

void network::socket::UnixUDPSocket::broadcast(const std::vector<uint8_t> &data) {
    if (status == STOPPING)
        return;
    if (status != CONNECTED)
        throw std::runtime_error("Can't send if socket isn't running");
    if (type == SERVER) {
        for (auto &client : clients) {
            if (client.status == CONNECTED)
                sendto(mainSocketFd, data.data(), data.size(), 0, (sockaddr *) &client.client, sizeof(client.client));
        }
    } else {
        sendto(mainSocketFd, data.data(), data.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));
    }
}

void network::socket::UnixUDPSocket::send(const std::vector<uint8_t> &data, unsigned long dest) {
    if (status == STOPPING)
        return;
    if (status != CONNECTED)
        throw std::runtime_error("Can't send if socket isn't running");
    if (type == SERVER) {
        for (auto &client : clients) {
            if (getClientId(client.client) == dest && (client.status == CONNECTED || client.status == CONNECTING)) {
                sendto(mainSocketFd, data.data(), data.size(), 0, (sockaddr *) &client.client, sizeof(client.client));
                return;
            }
        }
    } else {
        sendto(mainSocketFd, data.data(), data.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));
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
