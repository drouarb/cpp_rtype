//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_ENTITYACTION_HH
#define CPP_RTYPE_ENTITYACTION_HH

#include <string>
#include <ostream>
#include "AEntity.hh"

namespace Server {

    /** \struct EntityAction
    *   \brief //TODO
    */

    class IEntity;

    struct EntityAction {
        std::string soundToPlay;
        bool destroy;
        IEntity *newEntity;

        EntityAction();

    };

     std::ostream &operator<<(std::ostream &os, const EntityAction &action);

}


#endif //CPP_RTYPE_ENTITYACTION_HH
