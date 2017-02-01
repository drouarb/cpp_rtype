//
// Created by drouar_b on 11/6/16.
//

#include <stdexcept>
#include <cstring>
#include "network/packet/APacketData.hh"

network::packet::APacketData::APacketData(PacketId id, t_rawdata *data):
        packetId(PACKET_ID_SIZE, id)
{
    if (data)
        this->data = *data;
}

network::packet::APacketData::~APacketData() {

}

void network::packet::APacketData::serialize(t_rawdata *data) const {
    utils::NetworkInteger packetSize(PACKET_SIZE_SIZE, this->data.size());

    packetId.serialize(data);
    packetSize.serialize(data);
    data->insert(data->end(), this->data.begin(), this->data.end());
}

t_rawdata::iterator network::packet::APacketData::deserialize(t_rawdata *data, t_rawdata::iterator it) {
    utils::NetworkInteger id(PACKET_ID_SIZE);
    utils::NetworkInteger size(PACKET_SIZE_SIZE);

    it = id.deserialize(data, it);
    if (id.getValue() != this->packetId.getValue())
        throw std::domain_error("Invalid packet id");
    it = size.deserialize(data, it);
    if (size.getValue() > data->end() - it)
        throw std::out_of_range("Not enough data in buffer to read packet");
    this->data.resize(size.getValue());
    memcpy(&this->data.front(), &(*it), size.getValue());
    return (it + size.getValue());
}

t_rawdata::iterator network::packet::APacketData::deserialize(t_rawdata *data) {
    return this->deserialize(data, data->begin());
}

void network::packet::APacketData::setData(t_rawdata *data) {
    this->data = *data;
}

const t_rawdata &network::packet::APacketData::getData() const {
    return this->data;
}

uint16_t network::packet::APacketData::getSize() const {
    return data.size();
}

network::packet::PacketId network::packet::APacketData::getPacketId() const {
    return static_cast<PacketId>(packetId.getValue());
}

void network::packet::APacketData::setSource(unsigned long src) {
    this->src = src;
}

unsigned long network::packet::APacketData::getSource() const {
    return this->src;
}
