//
// Created by greg on 30/12/16.
//

#ifndef CPP_RTYPE_EPOCH_HH
#define CPP_RTYPE_EPOCH_HH

#include <cstdint>

namespace helpers {

    class Epoch {
    public:
        static uint64_t getTimeMs();
        static uint64_t getTimeS();
    };

}


#endif //CPP_RTYPE_EPOCH_HH
