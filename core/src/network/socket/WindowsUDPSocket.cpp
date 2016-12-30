//
// Created by drouar_b on 12/6/16.
//

#include <cstring>
#include <stdexcept>
#include <network/packet/PacketSyn.hh>
#include <network/packet/PacketSynAck.hh>
#include <network/packet/PacketAck.hh>
#include <network/packet/PacketPing.hh>
#include <network/packet/PacketPong.hh>
#include <network/packet/PacketDisconnect.hh>
#include "network/socket/WindowsUDPSocket.hh"

network::socket::WindowsUDPSocket::WindowsUDPSocket(unsigned short port) : type(network::socket::ISocket::SERVER), status(DISCONNECTED), thread(NULL) {
    WSADATA wsaData = { 0 };
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    memset(&mainSocket, 0, sizeof(mainSocket));
    memset(&pollfd, 0, sizeof(pollfd));
    mainSocket.sin_family = AF_INET;
    mainSocket.sin_port = htons(port);
    mainSocket.sin_addr.s_addr = htonl(INADDR_ANY);
    pollfd.events = POLLIN;
}

network::socket::WindowsUDPSocket::WindowsUDPSocket(const std::string &address, unsigned short port) : type(network::socket::ISocket::CLIENT), status(DISCONNECTED), thread(NULL) {
    WSADATA wsaData = { 0 };
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    memset(&mainSocket, 0, sizeof(mainSocket));
    memset(&pollfd, 0, sizeof(pollfd));
    mainSocket.sin_family = AF_INET;
    mainSocket.sin_port = htons(port);
    pollfd.events = POLLIN;
    if ((mainSocket.sin_addr.s_addr = inet_addr(address.c_str())) == 0)
        throw std::runtime_error("WindowsUDPSocket Invalid ip");
}

network::socket::WindowsUDPSocket::~WindowsUDPSocket() {
    this->stop();
}

bool network::socket::WindowsUDPSocket::run() {
    if (status != DISCONNECTED)
        throw std::runtime_error("WindowsUDPSocket Already running");
    init();
    if (type == CLIENT)
        thread = new Thread<void (WindowsUDPSocket::*)(), WindowsUDPSocket*>(&WindowsUDPSocket::clientPoll, this);
    else
        thread = new Thread<void (WindowsUDPSocket::*)(), WindowsUDPSocket*>(&WindowsUDPSocket::serverPoll, this);
    return true;
}

bool network::socket::WindowsUDPSocket::stop() {
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

void network::socket::WindowsUDPSocket::init() {
    if (type == CLIENT)
        clientInit();
    else
        serverInit();
}

void network::socket::WindowsUDPSocket::clientInit() {
    status = CONNECTING;

    if ((mainSocketFd = ::socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        status = DISCONNECTED;
        throw std::runtime_error("WindowsUDPSocket can't instantiate socket");
    }
    
    clientHandshake();
    sw.set();
    npings = 0;
    status = CONNECTED;
}

void network::socket::WindowsUDPSocket::serverInit() {
    status = CONNECTING;

    if ((mainSocketFd = ::socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        status = DISCONNECTED;
        throw std::runtime_error("WindowsUDPSocket can't instantiate socket");
    }
    if (bind(mainSocketFd, (struct sockaddr *) &mainSocket, sizeof(mainSocket)) == -1) {
        close(mainSocketFd);
        status = DISCONNECTED;
        throw std::runtime_error("WindowsUDPSocket can't bind port");
    }

    status = CONNECTED;
}

void network::socket::WindowsUDPSocket::poll() {
    if (status != DISCONNECTED)
        throw std::runtime_error("WindowsUDPSocket Already running");
    init();
    if (type == CLIENT)
        clientPoll();
    else
        serverPoll();
}

void network::socket::WindowsUDPSocket::serverPoll() {
    bool found;
    struct sockaddr_in recvSocket;
    int recvSocketLen = sizeof(recvSocket);
    std::vector<uint8_t> buffer(SOCKET_BUFFER);

    while (status == CONNECTED) {
        pollfd.fd = mainSocketFd;
        if (::WSAPoll(&pollfd, 1, POLL_TIMEOUT) && status == CONNECTED) {
            recvfrom(mainSocketFd, (char *)buffer.data(), SOCKET_BUFFER, 0, (struct sockaddr *) &recvSocket, &recvSocketLen);
            found = false;
            for (auto it = clients.begin(); it != clients.end(); it++) {
                if (getClientId((*it).client) == getClientId(recvSocket)) {
                    found = true;
                    (*it).sw.set();
                    (*it).npings = 0;
                    if ((*it).status == CONNECTED)
                        handleData(buffer, (*it).client);
                    if ((*it).status == CONNECTING)
                        if (!serverHandshake(buffer, (*it), ACK))
                            clients.erase(it);
                    break;
                }
            }
            if (!found) {
                clients.emplace_back();
                clients.back().status = CONNECTING;
                memcpy(&clients.back().client, &recvSocket, sizeof(recvSocket));
                if (!serverHandshake(buffer, clients.back(), SYNACK))
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
            sendto(mainSocketFd, (char *)buffer.data(), buffer.size(), 0, (sockaddr *) &client.client, sizeof(client.client));
    }
    clients.resize(0);
    close(mainSocketFd);
    status = DISCONNECTED;
}

bool network::socket::WindowsUDPSocket::serverHandshake(std::vector<uint8_t> &data, struct s_UDPClient &client,
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

void network::socket::WindowsUDPSocket::serverTimeout() {
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

void network::socket::WindowsUDPSocket::clientPoll() {
    std::vector<uint8_t> buffer(SOCKET_BUFFER);

    pollfd.fd = mainSocketFd;
    while (status == CONNECTED) {
        if (::WSAPoll(&pollfd, 1, POLL_TIMEOUT) && status == CONNECTED) {
            recv(mainSocketFd, (char *)buffer.data(), buffer.size(), 0);
            npings = 0;
            sw.set();
            handleData(buffer, mainSocket);
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

void network::socket::WindowsUDPSocket::clientHandshake() {
    std::vector<uint8_t> buff;
    packet::PacketSyn packetSyn;
    packet::PacketSynAck packetSynAck;
    packet::PacketAck packetAck;

    syn = (uint16_t) rand();
    packetSyn.setSyn(syn);
    packetSyn.serialize(&buff);
    sendto(mainSocketFd, (char *)buff.data(), buff.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));

    pollfd.fd = mainSocketFd;
    if (::WSAPoll(&pollfd, 1, HANDSHAKE_TIMEOUT) == 0)
        throw std::runtime_error("Client socket no handshake received");
    buff.resize(SOCKET_BUFFER);
    recv(mainSocketFd, (char *)buff.data(), SOCKET_BUFFER, 0);
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
    sendto(mainSocketFd, (char *)buff.data(), buff.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));
}

void network::socket::WindowsUDPSocket::clientTimeout() {
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

void network::socket::WindowsUDPSocket::handleData(const std::vector<uint8_t> &data, const struct sockaddr_in &client) {
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

void network::socket::WindowsUDPSocket::clientDisconnect() {
    status = DISCONNECTED;
    for (auto &l : disconnectionListeners) {
        l->notify(getClientId(mainSocket));
    }
    close(mainSocketFd);
}

void network::socket::WindowsUDPSocket::serverDisconnect(const struct sockaddr_in &client) {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if (getClientId((*it).client) == getClientId(client)) {
            for (auto &l : disconnectionListeners)
                l->notify(getClientId((*it).client));
            clients.erase(it);
            return;
        }
    }
}

void network::socket::WindowsUDPSocket::broadcast(const std::vector<uint8_t> &data) {
    if (status == STOPPING)
        return;
    if (status != CONNECTED)
        throw std::runtime_error("Can't send if socket isn't running");
    if (type == SERVER) {
        for (auto &client : clients) {
            if (client.status == CONNECTED)
                sendto(mainSocketFd, (char *)data.data(), data.size(), 0, (sockaddr *) &client.client, sizeof(client.client));
        }
    } else {
        sendto(mainSocketFd, (char *)data.data(), data.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));
    }
}

void network::socket::WindowsUDPSocket::send(const std::vector<uint8_t> &data, unsigned long dest) {
    if (status == STOPPING)
        return;
    if (status != CONNECTED)
        throw std::runtime_error("Can't send if socket isn't running");
    if (type == SERVER) {
        for (auto &client : clients) {
            if (getClientId(client.client) == dest && (client.status == CONNECTED || client.status == CONNECTING)) {
                sendto(mainSocketFd, (char *)data.data(), data.size(), 0, (sockaddr *) &client.client, sizeof(client.client));
                return;
            }
        }
    } else {
        sendto(mainSocketFd, (char *)data.data(), data.size(), 0, (sockaddr *) &mainSocket, sizeof(mainSocket));
    }
}

unsigned long network::socket::WindowsUDPSocket::getClientId(const struct sockaddr_in &client) {
    unsigned long id = client.sin_addr.s_addr;
    id <<= 16;
    id |= client.sin_port;
    return id;
}

void
network::socket::WindowsUDPSocket::registerConnectionListener(network::listener::ISocketConnectionListener *listener) {
    connectionListeners.push_front(listener);
}

void
network::socket::WindowsUDPSocket::unregisterConnectionListener(network::listener::ISocketConnectionListener *listener) {
    connectionListeners.remove(listener);
}

void network::socket::WindowsUDPSocket::registerDisconnectionListener(
        network::listener::ISocketDisconnectionListener *listener) {
    disconnectionListeners.push_front(listener);
}

void network::socket::WindowsUDPSocket::unregisterDisconnectionListener(
        network::listener::ISocketDisconnectionListener *listener) {
    disconnectionListeners.remove(listener);
}

void network::socket::WindowsUDPSocket::registerDataListener(network::listener::ISocketDataListener *listener) {
    dataListeners.push_front(listener);
}

void network::socket::WindowsUDPSocket::unregisterDataListener(network::listener::ISocketDataListener *listener) {
    dataListeners.remove(listener);
}

network::socket::ISocket::e_socketType network::socket::WindowsUDPSocket::getType() {
    return type;
}

network::socket::ISocket::e_socketStatus network::socket::WindowsUDPSocket::getStatus() {
    return status;
}
