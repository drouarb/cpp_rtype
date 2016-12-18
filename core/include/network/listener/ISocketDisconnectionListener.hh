//
// Created by drouar_b on 11/13/16.
//

#ifndef CPP_RTYPE_ISOCKETDISCONNECTIONLISTENER_HH
#define CPP_RTYPE_ISOCKETDISCONNECTIONLISTENER_HH

namespace network {
    namespace listener {
        class ISocketDisconnectionListener {
        public:
            virtual ~ISocketDisconnectionListener() { };

            virtual void notify(unsigned long fd) = 0;
        };
    }
}

#endif //CPP_RTYPE_ISOCKETDISCONNECTIONLISTENER_HH
