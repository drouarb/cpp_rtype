//
// Created by drouar_b on 11/11/16.
//

#include <stdexcept>
#include "network/utils/NetworkVector.hh"

network::utils::NetworkVector::NetworkVector(uint8_t lensize, std::vector<INetworkUtil *> schema):
        lensize(lensize), schema(schema) {
    if (lensize > sizeof(uint64_t) || lensize == 0)
        throw std::length_error("Invalid Network Vector len size " + lensize);
}

network::utils::NetworkVector::~NetworkVector() {
    for (auto s : schema) {
        delete (s);
    }
    for (auto d : data) {
        for (auto u : d) {
            delete(u);
        }
    }
}

uint16_t network::utils::NetworkVector::getSize() const {
    uint16_t datasize = 0;

    for (auto d : data) {
        for (auto u : d) {
            datasize += u->getSize();
        }
    }
    return datasize + lensize;
}

void network::utils::NetworkVector::serialize(t_rawdata *data) const {
    NetworkInteger size(lensize, this->data.size());

    size.serialize(data);
    for (auto d : this->data) {
        for (auto u : d) {
            u->serialize(data);
        }
    }
}

t_rawdata::iterator network::utils::NetworkVector::deserializeSchema(t_rawdata *data, t_rawdata::iterator it) {
    std::vector<INetworkUtil *> clones;

    for (auto s : schema) {
        clones.push_back(s->clone());
        try {
            it = clones.back()->deserialize(data, it);
        } catch (std::exception *e) {
            for (auto c : clones) {
                delete(c);
            }
            throw e;
        }
    }
    this->data.push_back(clones);
    return (it);
}

t_rawdata::iterator network::utils::NetworkVector::deserialize(t_rawdata *data, t_rawdata::iterator it) {
    NetworkInteger size(lensize);

    it = size.deserialize(data, it);
    for (auto d : this->data) {
        for (auto u : d) {
            delete(u);
        }
    }
    this->data.resize(0);
    for (size_t i = 0; i < size.getValue(); i++) {
        it = deserializeSchema(data, it);
    }
    return it;
}

t_rawdata::iterator network::utils::NetworkVector::deserialize(t_rawdata *data) {
    return this->deserialize(data, data->begin());
}

network::utils::INetworkUtil *network::utils::NetworkVector::clone() {
    std::vector<INetworkUtil *> clone;

    for (auto s : schema) {
        clone.push_back(s->clone());
    }
    return new NetworkVector(lensize, clone);
}

std::vector<network::utils::INetworkUtil *> &network::utils::NetworkVector::operator[](size_t idx) {
    if (idx >= data.size())
        this->resize(idx + 1);
    return data[idx];
}

std::vector<network::utils::INetworkUtil *> network::utils::NetworkVector::front() {
    return data.front();
}

std::vector<network::utils::INetworkUtil *> network::utils::NetworkVector::back() {
    return data.back();
}

void network::utils::NetworkVector::resize(size_t size) {
    std::vector<INetworkUtil *> clone(schema.size(), NULL);

    if (size < data.size()) {
        for (size_t i = size; i < data.size(); i++) {
            for (auto u : data[i])
                delete(u);
        }
        data.resize(size);
    }
    else {
        for (size_t i = data.size(); i < size; i++) {
            for (size_t j = 0; j < clone.size(); j ++) {
                clone[j] = schema[j]->clone();
            }
            data.push_back(clone);
        }
    }
}

size_t network::utils::NetworkVector::size() {
    return data.size();
}

