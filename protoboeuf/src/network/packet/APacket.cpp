//
// Created by drouar_b on 11/2/16.
//

#include <stdexcept>
#include "network/packet/APacket.hh"

network::packet::APacket::APacket(PacketId id, std::vector<utils::INetworkUtil *> schema):
        packetId(PACKET_ID_SIZE, id),
        schema(schema)
{ }


network::packet::APacket::~APacket() {
    for (auto it = schema.begin(); it != schema.end(); it++) {
        delete(*it);
    }
}

void network::packet::APacket::serialize(t_rawdata *data) const {
    packetId.serialize(data);
    utils::NetworkInteger(PACKET_SIZE_SIZE, this->getSize()).serialize(data);
    for (auto it = schema.begin(); it != schema.end(); it++) {
        (*it)->serialize(data);
    }
}

t_rawdata::iterator network::packet::APacket::deserialize(t_rawdata *data) {
    return this->deserialize(data, data->begin());
}

t_rawdata::iterator network::packet::APacket::deserialize(t_rawdata *data, t_rawdata::iterator it) {
    utils::NetworkInteger id(PACKET_ID_SIZE);
    utils::NetworkInteger size(PACKET_SIZE_SIZE);

    it = id.deserialize(data, it);
    if (id.getValue() != this->packetId.getValue())
        throw std::domain_error("Invalid packet id");
    it = size.deserialize(data, it);
    if (size.getValue() > data->end() - it)
        throw std::out_of_range("Not enough data in buffer to read packet");
    for (auto nuIt = schema.begin(); nuIt != schema.end(); nuIt++) {
        it = (*nuIt)->deserialize(data, it);
    }
    return it;
}

uint16_t network::packet::APacket::getSize() const {
    uint16_t size = 0;

    for (auto it = schema.begin(); it != schema.end(); it++) {
        size += (*it)->getSize();
    }
    return size;
}

network::packet::PacketId network::packet::APacket::getPacketId() const {
    return static_cast<PacketId>(packetId.getValue());
}

void network::packet::APacket::setSource(int src) {
    this->src = src;
}

int network::packet::APacket::getSource() const {
    return this->src;
}
