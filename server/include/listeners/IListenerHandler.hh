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
        virtual void clientRegister(int src, const std::string &name)= 0;
        virtual void clientDisconnect(int src)= 0;
        virtual void clientJoin(int src, gameId_t game)= 0;
        virtual void clientPlayerAttack(int src, attackId_t attackId)= 0;
        virtual void clientPlayerMove(int src, uint16_t vectX, uint16_t vectY)= 0;
        virtual void clientPlayerQuit(int src)= 0;
    };
}

#endif //CPP_RTYPE_ILISTENERHANDLER_HH
