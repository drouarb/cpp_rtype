//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketPlaySound.hh"
network::packet::PacketPlaySound::PacketPlaySound(uint32_t tick, uint32_t eventId, const std::string &SoundName) :
        APacket
                (
                        PLAY_SOUND,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(4, eventId),
                                new utils::NetworkString(SoundName.c_str())
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

void network::packet::PacketPlaySound::setSoundName(const std::string &SoundName)
{
    SET_NETSTR(schema, 2, SoundName);
}

network::utils::NetworkString network::packet::PacketPlaySound::getSoundName() const
{
    return GET_NETSTR(schema, 2);
}
