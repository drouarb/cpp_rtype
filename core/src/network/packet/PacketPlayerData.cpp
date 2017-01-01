//
// trouve_b
//

#include "network/packet/PacketPlayerData.hh"

network::packet::PacketPlayerData::~PacketPlayerData()
{}

network::packet::PacketPlayerData::PacketPlayerData(uint32_t id, uint8_t nbAttack) :

        APacket
                (
                        PLAYER_DATA,
                        {
                                new utils::NetworkInteger(4, id),
                                new utils::NetworkInteger(1, nbAttack)
                        }
                )
{

}

void network::packet::PacketPlayerData::setPlayerId(uint32_t id) {
    SET_NETINT(schema, 0, id);
}

uint32_t network::packet::PacketPlayerData::getPlayerId() const {
    return GET_NETINT(schema, 0);
}

void network::packet::PacketPlayerData::setNbAttack(uint8_t nb) {
    SET_NETINT(schema, 1 , nb);
}

uint8_t network::packet::PacketPlayerData::getNbAttack() const {
    return GET_NETINT(schema, 1);
}
