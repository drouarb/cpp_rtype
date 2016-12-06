//
// Created by drouar_b on 12/6/16.
//

#ifndef CPP_RTYPE_UNIXUDPSOCKET_HH
#define CPP_RTYPE_UNIXUDPSOCKET_HH

#include "ISocket.hh"

namespace network {
    namespace socket {
        /*!
         * @class UnixUDPSocket
         * @brief UDP socket handler for UNIX systems
         */
        class UnixUDPSocket: public ISocket {
        public:
            virtual bool run();
            virtual void poll();
            virtual bool stop();
            virtual void broadcast(std::vector<uint8_t> *data);
            virtual void send(std::vector<uint8_t> *data, int dest);
            virtual void registerConnectionListener(listener::ISocketConnectionListener *listener);
            virtual void unregisterConnectionListener(listener::ISocketConnectionListener *listener);
            virtual void registerDisconnectionListener(listener::ISocketDisconnectionListener *listener);
            virtual void unregisterDisconnectionListener(listener::ISocketDisconnectionListener *listener);
            virtual void registerDataListener(listener::ISocketDataListener *listener);
            virtual void unregisterDataListener(listener::ISocketDataListener *listener);
        };
    }
}

#endif //CPP_RTYPE_UNIXUDPSOCKET_HH
