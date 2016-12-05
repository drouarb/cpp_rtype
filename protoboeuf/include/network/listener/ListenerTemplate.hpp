//
// Created by lewis_e on 10/21/16.
//

#ifndef LISTENERTEMPLATE_HPP_
#define LISTENERTEMPLATE_HPP_

#include "network/packet/IPacket.hh"
#include "APacketListener.hh"

namespace network
{
    template <typename PACKETTYPE, enum packet::PacketId packetId>
    class ListenerTemplate : virtual public listener::APacketListener
    {
    public:
        virtual ~ListenerTemplate()
        { }

    protected:
        ListenerTemplate() : listener::APacketListener(packetId)
        { }



        void notify(const packet::IPacket *packet)
        {
            if (packet->getPacketId() == this->getPacketId())
            {
                this->notify(static_cast<const PACKETTYPE *>(packet));
            }
        }

        virtual void notify(const PACKETTYPE *packet) = 0;
    };
};

#endif
