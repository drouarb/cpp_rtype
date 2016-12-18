//
// Created by greg on 08/12/2016.
//

#ifndef CPP_RTYPE_ILISTENERHANDLER_HH
#define CPP_RTYPE_ILISTENERHANDLER_HH

#include <string>
#include "definitions.hh"

namespace server {
    /**
     * @interface IListenerHandler
     * @brief Interface used by all listener
     */
    class IListenerHandler {
    public:
        virtual void clientConnect(int src) = 0;

        virtual void clientRegister(int src, const std::string &name)= 0;

        virtual void clientDisconnect(int src)= 0;

        virtual void clientJoin(int src, gameId_t game)= 0;

        virtual void clientPlayerAttack(int src, attackId_t attackId, round_t tick)= 0;

        virtual void clientPlayerMove(int src, speed_t vectX, speed_t vectY)= 0;

        virtual void clientPlayerQuit(int src)= 0;

        virtual void askGame(int src)= 0;
    };
}

#endif //CPP_RTYPE_ILISTENERHANDLER_HH
