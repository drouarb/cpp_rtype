//
// Created by drouar_b on 11/29/16.
//

#ifndef CPP_RTYPE_PACKETFACTORY_HH
#define CPP_RTYPE_PACKETFACTORY_HH

#include <network/listener/ISocketConnectionListener.hh>
#include <network/listener/IPacketListener.hh>
#include <network/packet/IPacket.hh>
#include <string>

namespace network {
    class PacketFactory {
    public:
        PacketFactory(short port);
        PacketFactory(const std::string &address, short port);
        ~PacketFactory();

        void run();
        void poll();

        void send(const packet::IPacket &packet);
        void send(const packet::IPacket &packet, int fd);

        void registerConnectionListener(listener::ISocketConnectionListener *listener);
        void unregisterConnectionListener(listener::ISocketConnectionListener *listener);

        void registerListener(listener::IPacketListener *listener);
        void unregisterListener(listener::IPacketListener *listener);
    };
}


#endif //CPP_RTYPE_PACKETFACTORY_HH
