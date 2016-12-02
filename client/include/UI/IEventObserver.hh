//
// Created by jonas_e on 12/1/16.
//

#ifndef CPP_RTYPE_IEVENTOBSERVER_HH
#define CPP_RTYPE_IEVENTOBSERVER_HH

#include "IWindow.hh"

namespace UI {
    class IEventObserver {
    public:
        virtual ~IEventObserver(){};
        virtual void getEvent() = 0;
        virtual void listen(UI::IWindow *window) = 0;
    };
}

#endif //CPP_RTYPE_IEVENTOBSERVER_HH
