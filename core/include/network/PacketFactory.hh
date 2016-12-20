//
// Created by drouar_b on 11/29/16.
//

#ifndef CPP_RTYPE_PACKETFACTORY_HH
#define CPP_RTYPE_PACKETFACTORY_HH

#include <network/listener/ISocketConnectionListener.hh>
#include <network/listener/IPacketListener.hh>
#include <network/socket/ISocket.hh>
#include <network/packet/IPacket.hh>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <network/listener/PacketFactoryDataListener.hh>

namespace network {
    class PacketFactory {
    private:
        typedef packet::IPacket *(PacketFactory::* createPacketFunc)(unsigned long fd, const t_rawdata &data) const;

    public:
        PacketFactory(unsigned short port);
        PacketFactory(const std::string &address, unsigned short port);
        virtual ~PacketFactory();

        void run();
        void poll();
        void stop();

        void broadcast(const packet::IPacket &packet) const;

        virtual void send(const packet::IPacket &packet, unsigned long fd) const;

        void dataCallback(unsigned long fd, const std::vector<uint8_t> &data) const;

        void registerConnectionListener(listener::ISocketConnectionListener *listener);
        void unregisterConnectionListener(listener::ISocketConnectionListener *listener);

        void registerDisconnectionListener(listener::ISocketDisconnectionListener *listener);
        void unregisterDisconnectionListener(listener::ISocketDisconnectionListener *listener);

        void registerListener(listener::IPacketListener *listener);
        void unregisterListener(listener::IPacketListener *listener);

    private:
        socket::ISocket *socket;
        listener::PacketFactoryDataListener dataListener;

        template<class T>
        packet::IPacket *createPacket(unsigned long fd, const t_rawdata &data) const {
            T *packet = new T();
            //TODO Const ref protoboeuf
            packet->deserialize(const_cast<t_rawdata *>(&data));
            packet->setSource(fd);
            return packet;
        }

        void notifyPacket(network::packet::IPacket *packet) const;

        std::map<packet::PacketId, std::set<listener::IPacketListener *>> listeners;
        static const std::map<packet::PacketId, createPacketFunc> createMap;
    };
}


#endif //CPP_RTYPE_PACKETFACTORY_HH
