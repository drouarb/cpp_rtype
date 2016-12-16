//
// Created by jonas_e on 12/2/16.
//

#ifndef CPP_RTYPE_EVENTMANAGER_HH
#define CPP_RTYPE_EVENTMANAGER_HH

#include <SFML/Window/Keyboard.hpp>
#include "IEventHandler.hh"
#include "GameClient.hh"

namespace client {
    class EventManager : public IEventHandler {
    private:
        client::GameClient *gameClient;
    public:
        EventManager(client::GameClient *gameclient);

        ~EventManager();

        void onKeyPressed(short key);

        void onKeyRealease(short key);

        void onMouseRealease(short x, short y);

    };
}


#endif //CPP_RTYPE_EVENTMANAGER_HH
