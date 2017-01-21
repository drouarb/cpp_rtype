//
// Created by celeriy on 11/12/16.
//

#ifndef CPP_RTYPE_IEVENTHANDLER_HH
#define CPP_RTYPE_IEVENTHANDLER_HH


namespace client {
    class IEventHandler {

    public:
        virtual  ~IEventHandler() {};

        virtual void onKeyPressed(short key) = 0;

        virtual void onKeyRelease(short key) = 0;

        virtual void onMouseRelease(short x, short y) = 0;

    };
}


#endif //CPP_RTYPE_IEVENTHANDLER_HH
