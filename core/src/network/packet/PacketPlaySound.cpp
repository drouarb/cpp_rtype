//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketPlaySound.hh"
network::packet::PacketPlaySound::PacketPlaySound(uint32_t tick, uint32_t eventId, uint16_t SoundName) :
        APacket
                (
                        PLAY_SOUND,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(4, eventId),
                                new utils::NetworkInteger(2, SoundName)
                        }
                )
{

}

network::packet::PacketPlaySound::~PacketPlaySound()
{

}

void network::packet::PacketPlaySound::setTick(uint32_t tick)
{
    SET_NETINT(schema, 0, tick);
}

uint32_t network::packet::PacketPlaySound::getTick() const
{
    return GET_NETINT(schema, 0);
}

void network::packet::PacketPlaySound::setEventId(uint32_t id)
{
    SET_NETINT(schema, 1, id);
}

uint32_t network::packet::PacketPlaySound::getEventId() const
{
    return GET_NETINT(schema, 1);
}

void network::packet::PacketPlaySound::setSoundName(uint16_t SoundName)
{
    SET_NETINT(schema, 2 , SoundName);
}

uint16_t network::packet::PacketPlaySound::getSoundName() const
{
    return GET_NETINT(schema, 2);
}
