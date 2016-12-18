//
// trouve_b
//

#include "network/packet/PacketPlayerData.hh"

network::packet::PacketPlayerData::~PacketPlayerData()
{}

network::packet::PacketPlayerData::PacketPlayerData(uint16_t id, uint8_t nbAttack) :

        APacket
                (
                        PLAYER_DATA,
                        {
                                new utils::NetworkInteger(2, id),
                                new utils::NetworkInteger(1, nbAttack)
                        }
                )
{

}

void network::packet::PacketPlayerData::setPlayerId(uint16_t id) {
    SET_NETINT(schema, 0, id);
}

uint16_t network::packet::PacketPlayerData::getPlayerId() const {
    return GET_NETINT(schema, 0);
}

void network::packet::PacketPlayerData::setNbAttack(uint8_t nb) {
    SET_NETINT(schema, 1 , nb);
}

uint8_t network::packet::PacketPlayerData::getNbAttack() const {
    return GET_NETINT(schema, 1);
}