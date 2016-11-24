//
// Created by celeriy on 23/11/16.
//

#include "network/packet/PacketPlayerAttack.hh"

network::packet::PacketPlayerAttack::PacketPlayerAttack(uint32_t tick, uint8_t attackId) :
        APacket
                (
                        PLAYER_ATTACK,
                        {
                                new utils::NetworkInteger(4, tick),
                                new utils::NetworkInteger(1, attackId)
                        }
                )
{

}

network::packet::PacketPlayerAttack::~PacketPlayerAttack()
{

}

void network::packet::PacketPlayerAttack::setTick(uint32_t tick)
{
    SET_NETINT(schema, 0, tick);
}

uint32_t network::packet::PacketPlayerAttack::getTick() const
{
    return GET_NETINT(schema, 0);
}

void network::packet::PacketPlayerAttack::setAttackId(uint8_t id)
{
    SET_NETINT(schema, 1, id);
}

uint8_t network::packet::PacketPlayerAttack::getAttackId() const
{
    return GET_NETINT(schema, 1);
}
