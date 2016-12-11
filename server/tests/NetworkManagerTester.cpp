//
// Created by greg on 09/12/2016.
//

#include <iostream>
#include "ProjTester.hpp"

void toTest(NetworkManagerTest &, CoreTest &);

void reset() {
    for (int i = 0; i != END; ++i) {
        status[static_cast<METHOD_CALLED>(i)] = false;
    }
}

int main() {
    reset();
    NetworkManagerTest networkManagerTest(nullptr);
    CoreTest core("../levels/", &networkManagerTest);
    networkManagerTest.setCore(&core);

    toTest(networkManagerTest, core);
}