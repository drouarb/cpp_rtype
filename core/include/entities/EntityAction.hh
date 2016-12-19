//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_ENTITYACTION_HH
#define CPP_RTYPE_ENTITYACTION_HH

#include <string>
#include <ostream>
#include <Definitions.hh>

namespace server {

    /** \struct EntityAction
     *  \brief Actions done by the entity at a game round. Will be stored in the simulation.
     */

    class ADynamicObject;

    struct EntityAction {
        std::string soundToPlay;
        bool destroy;
        ADynamicObject *newEntity;
        speed_t speedX;
        speed_t speedY;
        hp_t hp;

        EntityAction();
    };

     std::ostream &operator<<(std::ostream &os, const EntityAction &action);

}


#endif //CPP_RTYPE_ENTITYACTION_HH
