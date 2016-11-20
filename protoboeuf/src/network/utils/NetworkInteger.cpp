//
// Created by drouar_b on 10/25/16.
//

#include <stdexcept>
#include "network/utils/NetworkInteger.hh"

network::utils::NetworkInteger::NetworkInteger(uint8_t size, ssize_t i) : size(size), i(i) {
    if (size > sizeof(uint64_t) || size == 0)
        throw std::length_error("Invalid Network Integer number " + size);
}

network::utils::NetworkInteger::~NetworkInteger() {}

void network::utils::NetworkInteger::serialize(t_rawdata *data) const {
    const uint8_t *nb;

    nb = reinterpret_cast<const uint8_t *>(&this->i);
    for (int i = 0; i < this->size; i++) {
        data->push_back(nb[i]);
    }
}

t_rawdata::iterator network::utils::NetworkInteger::deserialize(t_rawdata *data, t_rawdata::iterator it) {
    if ((&data->back() - &(*it)) < size - 1)
        throw std::out_of_range("Can't read number of NetworkInteger");
    this->i = (*reinterpret_cast<ssize_t *>(&(*it))) & this->intMask[this->size];
    return it + this->getSize();
}

t_rawdata::iterator network::utils::NetworkInteger::deserialize(t_rawdata *data) {
    return this->deserialize(data, data->begin());
}

ssize_t network::utils::NetworkInteger::getValue() const {
    return i;
}

ssize_t network::utils::NetworkInteger::operator=(ssize_t val) {
    return (i = val);
}

void network::utils::NetworkInteger::setValue(ssize_t val) {
    i = val;
}

uint16_t network::utils::NetworkInteger::getSize() const {
    return this->size;
}

network::utils::INetworkUtil *network::utils::NetworkInteger::clone() {
    return new NetworkInteger(size);
}

const std::vector<uint64_t> network::utils::NetworkInteger::intMask = {
        0x0000000000000000,
        0x00000000000000FF,
        0x000000000000FFFF,
        0x0000000000FFFFFF,
        0x00000000FFFFFFFF,
        0x000000FFFFFFFFFF,
        0x0000FFFFFFFFFFFF,
        0x00FFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
};


