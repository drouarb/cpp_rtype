//
// Created by greg on 08/12/2016.
//

#ifndef CPP_RTYPE_IPLAYER_HH
#define CPP_RTYPE_IPLAYER_HH

namespace server {
    class IPlayer {
    public:
        virtual void shoot(attackId_t attackId) = 0;
    };
}

#endif //CPP_RTYPE_IPLAYER_HH
