//
// Created by drouar_b on 11/13/16.
//

#ifndef CPP_RTYPE_ISOCKETCONNECTIONLISTENER_HH
#define CPP_RTYPE_ISOCKETCONNECTIONLISTENER_HH

namespace network {
    namespace listener {
        class ISocketConnectionListener {
        public:
            virtual ~ISocketConnectionListener() { };

            virtual void notify(int fd) = 0;
        };
    }
}

#endif //CPP_RTYPE_ISOCKETCONNECTIONLISTENER_HH
