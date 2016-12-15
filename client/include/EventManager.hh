//
// Created by jonas_e on 12/2/16.
//

#ifndef CPP_RTYPE_EVENTMANAGER_HH
#define CPP_RTYPE_EVENTMANAGER_HH

#include <SFML/Window/Keyboard.hpp>
#include "IEventHandler.hh"

namespace client {
    class EventManager : public IEventHandler {
    public:
        EventManager();

        ~EventManager();

        void onKeyPressed(short key);

        void onKeyRealease(short key);

        void onMouseRealease(short x, short y);

    };
}


#endif //CPP_RTYPE_EVENTMANAGER_HH
