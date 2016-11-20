//
// Created by drouar_b on 11/11/16.
//

#include <stdexcept>
#include <assert.h>
#include <iostream>
#include "network/utils/NetworkString.cpp"
#include "network/utils/NetworkInteger.cpp"
#include "network/utils/NetworkVector.cpp"

using namespace network;
using namespace network::utils;

int main()
{
    int test;
    t_rawdata data;
    t_rawdata::iterator it;
    NetworkInteger len(2);
    NetworkVector *v = new NetworkVector(2, {});

    std::vector<int> *toto = new std::vector<int>;

    std::cout << "Resize tests" << std::endl;
    v->resize(0);
    v->resize(10);
    v->resize(0);

    std::cout << "Size tests" << std::endl;
    assert(v->getSize() == 2);
    v = new NetworkVector(2, {new NetworkString, new NetworkInteger(2)});

    SET_NETSTR((*v)[0], 0, "Hi");
    SET_NETINT((*v)[0], 1, 0);
    assert(v->getSize() == 8);

    SET_NETSTR((*v)[1], 0, "KEK");
    SET_NETINT((*v)[1], 1, 50);
    assert(v->getSize() == 15);

    std::cout << "Serialization tests" << std::endl;
    v->serialize(&data);
    assert(data.size() == v->getSize());
    it = len.deserialize(&data);
    assert(len.getValue() == 2);
    assert(len.getValue() == v->size());

    NetworkString strs1;
    NetworkInteger nbs1(2);
    NetworkString strs2;
    NetworkInteger nbs2(2);
    it = strs1.deserialize(&data, it);
    it = nbs1.deserialize(&data, it);
    it = strs2.deserialize(&data, it);
    it = nbs2.deserialize(&data, it);
    assert(strs1.compare("Hi") == 0);
    assert(nbs1.getValue() == 0);
    assert(strs2.compare("KEK") == 0);
    assert(nbs2.getValue() == 50);

    std::cout << "Deserialization tests" << std::endl;
    v->deserialize(&data);
    assert(GET_NETSTR((*v)[0], 0).compare("Hi") == 0);
    assert(GET_NETINT((*v)[0], 1) == 0);
    assert(GET_NETSTR((*v)[1], 0).compare("KEK") == 0);
    assert(GET_NETINT((*v)[1], 1) == 50);

    std::cout << "Stress test & recursion" << std::endl;
    v = new NetworkVector(1, {
            new NetworkVector(1, {
                    new NetworkVector(1, {
                            new NetworkInteger(1),
                            new NetworkString
                    })
            })
    });
    v->resize(10);
    for (int i = 0; i < 10; i++) {
        GET_NETVEC((*v)[i], 0).resize(10);
        for (int j = 0; j < 10; j++) {
            GET_NETVEC(GET_NETVEC((*v)[i], 0)[j], 0).resize(10);
        }
    }
    data.resize(0);
    v->serialize(&data);
    v->deserialize(&data);
}