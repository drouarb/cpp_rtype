//
// Created by greg on 08/12/2016.
//

#ifndef CPP_RTYPE_ILISTENERHANDLER_HH
#define CPP_RTYPE_ILISTENERHANDLER_HH

#include <string>
#include "Definitions.hh"

namespace server {
    /**
     * @interface IListenerHandler
     * @brief Interface used by all listener
     */
    class IListenerHandler {
    public:
        virtual void clientConnect(clientId_t src) = 0;

        virtual void clientRegister(clientId_t src, const std::string &name)= 0;

        virtual void clientDisconnect(clientId_t src)= 0;

        virtual void clientJoin(clientId_t src, gameId_t game)= 0;

        virtual void clientPlayerAttack(clientId_t src, attackId_t attackId, round_t tick)= 0;

        virtual void clientPlayerMove(clientId_t src, speed_t vectX, speed_t vectY)= 0;

        virtual void clientPlayerQuit(clientId_t src)= 0;

        virtual void askGame(clientId_t src)= 0;
    };
}

#endif //CPP_RTYPE_ILISTENERHANDLER_HH
