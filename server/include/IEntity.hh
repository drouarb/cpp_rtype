//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_IENTITY_HH
#define CPP_RTYPE_IENTITY_HH

#include "EntityAction.hh"
#include "definitions.hh"

/** \def ENTRY_POINTS
 *  \brief Allow to create entry point for shared libairies
 */

#define ENTRY_POINTS(className) extern "C" { \
    void *create_entity(uint16_t entityId) { return new className(entityId); } \
    }


namespace server {

    /** \interface IEntity
     *  \brief //TODO
     */

    struct EntityAction;

    typedef int entityId_t;

    enum Team : unsigned int
    {
        NA      = 0,    //not applicable (non-actor entities)
        PLAYER  = 1,    //players' team
        FOE     = 2     //default team for enemies
        // Other values greater than 2 may be used in the dynamic libraries. The server is not concerned by them.
    };

    class IEntity {
    public:

        static IEntity * make(const std::string & path);

        /**
         * The entityId is given by the server. The object should not choose its own entityId.
         */
        virtual void setEntityId(entityId_t) = 0;
        /**
         * Just return the set entityId.
         */
        virtual entityId_t getEntityId() = 0;

        virtual Team getTeam() = 0;
        virtual std::string & getSprite() = 0;

        /*
         * Those setters are there mainly for the simulation, so just obey the server and set the variables accordingly.
         */
        //TODO: ideally, the object created by the dynamic library should not have access to some of these variables.

        virtual void setPosX(pos_t) = 0;
        virtual pos_t getPosX() = 0;
        virtual void setPosY(pos_t) = 0;
        virtual pos_t getPosY() = 0;
        virtual void setSpeedX(speed_t) = 0;
        virtual speed_t getSpeedX() = 0;
        virtual void setSpeedY(speed_t) = 0;
        virtual speed_t getSpeedY() = 0;
        virtual void modHp(int) = 0;
        virtual int getHp() = 0;
        virtual void destroy() = 0;
        virtual void restore() = 0;
        virtual bool isDestroyed() = 0;

        /**
         * This method is always called just before nextAction().
         * It informs the entity that it just collided with the Entity passed as parameter.
         * If the instance where collide() is called is an actor, it should check the colliding entity for damage.
         * This method may be called multiple times before nextAction() is called, if there are multiple collisions.
         */
        virtual void collide(IEntity *)= 0;
        /**
         * This method is called at each game round. Here, the entity can chose to do anything (or nothing).
         * Playing a sound, destroying oneself or creating a new entity must be done via EntityAction.
         * Any other action can be done from inside the class. The server will then detect the action automatically comparing the fields to the previous ones.
         * The returned EntityAction must be dynamically alloc'd, and will be deleted by the caller.
         */
        virtual EntityAction * nextAction() = 0;
    };
}

#endif //CPP_RTYPE_IENTITY_HH
