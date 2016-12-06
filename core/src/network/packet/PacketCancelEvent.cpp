//
// Created by celeriy on 24/11/16.
//

#include "network/packet/PacketCancelEvent.hh"

network::packet::PacketCancelEvent::~PacketCancelEvent()
{

}

void network::packet::PacketCancelEvent::setCancelEvent(uint32_t roomdId)
{
    SET_NETINT(schema, 0, roomdId);
}

uint32_t network::packet::PacketCancelEvent::getCancelEvent() const
{
    return GET_NETINT(schema, 0);
}

network::packet::PacketCancelEvent::PacketCancelEvent(uint32_t eventId) :
        APacket(
                CANCEL_EVENT,
                {
                        new utils::NetworkInteger(4, eventId)
                }

        )
{}
