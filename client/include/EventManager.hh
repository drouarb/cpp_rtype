//
// Created by jonas_e on 12/2/16.
//

#ifndef CPP_RTYPE_EVENTMANAGER_HH
#define CPP_RTYPE_EVENTMANAGER_HH

namespace client {
    class EventManager {
    public:
        EventManager();
        ~EventManager();
        static void onKeyPressed(sf::Keyboard::Key key);
    };
}


#endif //CPP_RTYPE_EVENTMANAGER_HH
