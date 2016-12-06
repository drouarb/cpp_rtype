//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_ENTITYACTION_HH
#define CPP_RTYPE_ENTITYACTION_HH

#include <string>
#include <ostream>

namespace server {

    /** \struct EntityAction
    *   \brief Actions done by the entity at a game round. Will be stored in the simulation.
     *   Other actions (like movement and HP changing) will be done from inside the IEntity, and detected by the server automatically.
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
