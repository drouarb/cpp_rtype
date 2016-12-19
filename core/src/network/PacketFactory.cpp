//
// Created by drouar_b on 11/29/16.
//

#ifdef _WIN32
#include <network/socket/WindowsUDPSocket.hh>
#else
#include <network/socket/UnixUDPSocket.hh>
#endif

#include <network/packet/PacketErrorHandshake.hh>
#include <network/packet/PacketRegister.hh>
#include <network/packet/PacketDisconnect.hh>
#include <network/packet/PacketErrorList.hh>
#include <network/packet/PacketAskList.hh>
#include <network/packet/PacketGameList.hh>
#include <network/packet/PacketErrorGame.hh>
#include <network/packet/PacketJoin.hh>
#include <network/packet/PacketQuit.hh>
#include <network/packet/PacketEventError.hh>
#include <network/packet/PacketCancelEvent.hh>
#include <network/packet/PacketPlayerMove.hh>
#include <network/packet/PacketPlayerAttack.hh>
#include <network/packet/PacketSpawnEntity.hh>
#include <network/packet/PacketDeleteEntity.hh>
#include <network/packet/PacketUpdateEntity.hh>
#include <network/packet/PacketMoveEntity.hh>
#include <network/packet/PacketPlaySound.hh>
#include <network/packet/PacketErrorScore.hh>
#include <network/packet/PacketAskLeaderBoard.hh>
#include <network/packet/PacketLeaderBoard.hh>
#include "network/PacketFactory.hh"

network::PacketFactory::PacketFactory(unsigned short port): dataListener(*this) {
#ifdef _WIN32
    socket = new socket::WindowsUDPSocket(port);
#else
    socket = new socket::UnixUDPSocket(port);
#endif
    socket->registerDataListener(&dataListener);
}

network::PacketFactory::PacketFactory(const std::string &address, unsigned short port): dataListener(*this) {
#ifdef _WIN32
    socket = new socket::WindowsUDPSocket(address, port);
#else
    socket = new socket::UnixUDPSocket(address, port);
#endif
    socket->registerDataListener(&dataListener);
}

network::PacketFactory::~PacketFactory() {
    socket->stop();
    delete (socket);
}

void network::PacketFactory::run() {
    socket->run();
}

void network::PacketFactory::poll() {
    socket->poll();
}

void network::PacketFactory::stop() {
    socket->stop();
}

void network::PacketFactory::dataCallback(unsigned long fd, const std::vector<uint8_t> &data) const {
    packet::PacketId id;
    packet::IPacket *packet;
    std::vector<uint8_t> buff;

    buff.assign(data.begin(), data.end());
    while (buff.size()) {
        try {
            id = static_cast<packet::PacketId>(buff.at(0));
            packet = (packet::IPacket *) ((this->*(createMap.at(id)))(fd, buff));
        } catch (std::exception e) {
            return;
        }
        if (packet) {
            buff.erase(buff.begin(), buff.begin() + packet->getSize() + PACKET_HEADER_SIZE);
            this->notifyPacket(packet);
            delete (packet);
        }
    }
}

void network::PacketFactory::notifyPacket(network::packet::IPacket *packet) const {
    auto it = listeners.find(packet->getPacketId());

    if (it != listeners.end()) {
        for (auto &l : (*it).second) {
            l->notify(packet);
        }
    }
}

void network::PacketFactory::broadcast(const packet::IPacket &packet) const {
    std::vector<uint8_t> buffer;

    packet.serialize(&buffer);
    socket->broadcast(buffer);
}

void network::PacketFactory::send(const network::packet::IPacket &packet, unsigned long fd) const {
    std::vector<uint8_t> buffer;

    packet.serialize(&buffer);
    socket->send(buffer, fd);
}

void network::PacketFactory::registerListener(network::listener::IPacketListener *listener) {
    listeners[listener->getPacketId()].insert(listener);
}

void network::PacketFactory::unregisterListener(network::listener::IPacketListener *listener) {
    listeners[listener->getPacketId()].erase(listener);
}

void network::PacketFactory::registerConnectionListener(network::listener::ISocketConnectionListener *listener) {
    socket->registerConnectionListener(listener);
}

void network::PacketFactory::unregisterConnectionListener(network::listener::ISocketConnectionListener *listener) {
    socket->unregisterConnectionListener(listener);
}

void network::PacketFactory::registerDisconnectionListener(network::listener::ISocketDisconnectionListener *listener) {
    socket->registerDisconnectionListener(listener);
}

void
network::PacketFactory::unregisterDisconnectionListener(network::listener::ISocketDisconnectionListener *listener) {
    socket->unregisterDisconnectionListener(listener);
}

const std::map<network::packet::PacketId, network::PacketFactory::createPacketFunc> network::PacketFactory::createMap = {
        {packet::ERROR_HANDSHAKE, &PacketFactory::createPacket < packet::PacketErrorHandshake > },
        {packet::REGISTER,        &PacketFactory::createPacket < packet::PacketRegister > },
        {packet::DISCONNECT,      &PacketFactory::createPacket < packet::PacketDisconnect > },

        {packet::ERROR_LIST,      &PacketFactory::createPacket < packet::PacketErrorList > },
        {packet::ASK_LIST,        &PacketFactory::createPacket < packet::PacketAskList > },
        {packet::GAME_LIST,       &PacketFactory::createPacket < packet::PacketGameList > },

        {packet::ERROR_GAME,      &PacketFactory::createPacket < packet::PacketErrorGame > },
        {packet::JOIN,            &PacketFactory::createPacket < packet::PacketJoin > },
        {packet::QUIT,            &PacketFactory::createPacket < packet::PacketQuit > },

        {packet::EVENT_ERROR,     &PacketFactory::createPacket < packet::PacketEventError > },
        {packet::CANCEL_EVENT,    &PacketFactory::createPacket < packet::PacketCancelEvent > },
        {packet::PLAYER_MOVE,     &PacketFactory::createPacket < packet::PacketPlayerMove > },
        {packet::PLAYER_ATTACK,   &PacketFactory::createPacket < packet::PacketPlayerAttack > },
        {packet::SPAWN_ENTITY,    &PacketFactory::createPacket < packet::PacketSpawnEntity > },
        {packet::DELETE_ENTITY,   &PacketFactory::createPacket < packet::PacketDeleteEntity > },
        {packet::UPDATE_ENTITY,   &PacketFactory::createPacket < packet::PacketUpdateEntity > },
        {packet::MOVE_ENTITY,     &PacketFactory::createPacket < packet::PacketMoveEntity > },
        {packet::PLAY_SOUND,      &PacketFactory::createPacket < packet::PacketPlaySound > },

        {packet::ERROR_SCORE,     &PacketFactory::createPacket < packet::PacketErrorScore > },
        {packet::ASK_LEADERBOARD, &PacketFactory::createPacket < packet::PacketAskLeaderBoard > },
        {packet::LEADER_BOARD,    &PacketFactory::createPacket < packet::PacketLeaderBoard > },
};
