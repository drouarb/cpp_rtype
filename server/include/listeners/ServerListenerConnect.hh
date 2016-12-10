//
// Created by greg on 10/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERCONNECT_HH
#define CPP_RTYPE_SERVERLISTENERCONNECT_HH

#include "IListenerHandler.hh"
#include <network/listener/ISocketConnectionListener.hh>

namespace server {

    class ServerListenerConnect : public network::listener::ISocketConnectionListener {
        IListenerHandler *listenerHandler;
    public:
        ServerListenerConnect(IListenerHandler *listenerHandler);

        void notify(int fd) override;
    };

}

#endif //CPP_RTYPE_SERVERLISTENERCONNECT_HH
