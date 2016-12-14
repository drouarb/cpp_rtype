//
// Created by greg on 08/12/2016.
//

#ifndef CPP_RTYPE_IPLAYER_HH
#define CPP_RTYPE_IPLAYER_HH

#include "ADynamicObject.hh"

namespace server
{
    class APlayer : public ADynamicObject
    {
    public:
        virtual void shoot(attackId_t attackId) = 0;
        virtual void move(speed_t vectX, speed_t vectY) = 0;
    };
}

#endif //CPP_RTYPE_IPLAYER_HH
