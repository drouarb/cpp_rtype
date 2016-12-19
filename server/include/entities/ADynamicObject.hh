//
// Created by lewis_e on 12/12/16.
//

#ifndef CPP_RTYPE_ADYNAMICOBJECT_HH
#define CPP_RTYPE_ADYNAMICOBJECT_HH

#include "EntityAction.hh"
#include "EntityInitialization.hh"
#include "EntityData.hh"

namespace server
{
    class Entity;

    class ADynamicObject
    {
    public:
        virtual ~ADynamicObject() { }

        /**
         * This method is called before nextAction().
         * It informs the entity that it just collided with the Entity passed as parameter.
         * If the instance where collide() is called is an actor, it should check the colliding entity for damage.
         * This method may be called multiple times before nextAction() is called, if there are multiple collisions.
         */
        virtual void collide(const Entity &) = 0;
        /**
         * This method is called at each game round. Here, the entity can chose to do anything (or nothing).
         * The returned EntityAction contains all that the entity wants to do.
         * It must be dynamically alloc'd, and will be deleted by the caller. Must not be null.
         * The parameter is the current game round. It allows the entity to know the current 'time' of the game.
         * This 'round' can increment (as the game goes) or go back a few steps in case of a rewind of the simulation.
         */
        virtual EntityAction *act(round_t current_round) = 0;
        /**
         * This method is called when the object is first created.
         * The X and Y coordinates given in the EntityInitilization will be ignored if the entity was created by the level.
         * They will only be applied if the entity is created by another entity.
         */
        virtual EntityInitialization * initialize() = 0;
        /**
         * This method returns the damage that this entity causes when colliding with another entity.
         * May be null.
         * Is typically used for projectiles.
         * May be negative (for a boon for instance).
         */
        virtual hp_t getDamage() = 0;

        virtual bool collideWith(const Entity &) = 0;

        const EntityData * data;
    };
}

#endif //CPP_RTYPE_IDYNAMICOBJECT_HH
