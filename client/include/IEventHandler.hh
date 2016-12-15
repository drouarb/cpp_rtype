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

        virtual void onKeyRealease(short key) = 0;

        virtual void onMouseRealease(short x, short y) = 0;

    };
}


#endif //CPP_RTYPE_IEVENTHANDLER_HH
