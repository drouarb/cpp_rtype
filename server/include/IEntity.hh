//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_IENTITY_HH
#define CPP_RTYPE_IENTITY_HH

#include "EntityAction.hh"

/** \def ENTRY_POINTS
 *  \brief Allow to create entry point for shared libairies
 */

#define ENTRY_POINTS(className) extern "C" { \
    Server::IEntity *create_entity(uint16_t entityId) { return new className(entityId); } \
    }


namespace Server {

    /** \interface IEntity
     *  \brief //TODO
     */

    struct EntityAction;

    class IEntity {
    public:

        virtual void collide(IEntity *)= 0;

        virtual EntityAction *nextAction()= 0;
    };
}

#endif //CPP_RTYPE_IENTITY_HH
