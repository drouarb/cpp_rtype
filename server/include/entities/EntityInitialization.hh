//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_ENTITYINIT_HH
#define CPP_RTYPE_ENTITYINIT_HH

#include "EntityAction.hh"
#include "../definitions.hh"

namespace server
{
    struct EntityInitialization
    {
        pos_t posX;
        pos_t posY;
        std::string sprite;
        Team team;

        EntityAction action;

        EntityInitialization();
        EntityInitialization(const std::string & sprite);
    };
}


#endif //CPP_RTYPE_ENTITYACTION_HH
