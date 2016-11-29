//
// Created by drouar_b on 11/13/16.
//

#ifndef CPP_RTYPE_ISOCKETDATALISTENER_HH
#define CPP_RTYPE_ISOCKETDATALISTENER_HH

#include <vector>

namespace network {
    namespace listener {
        class ISocketDataListener {
        public:
            virtual ~ISocketDataListener() { };

            virtual void notify(int fd, std::vector<unsigned char> *data) = 0;
        };
    }
}

#endif //CPP_RTYPE_ISOCKETDATALISTENER_HH
