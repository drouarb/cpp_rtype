//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_PROJECTILE_HH
#define CPP_RTYPE_PROJECTILE_HH


#include <IEntity.hh>
#include "IDamager.hh"
#include <Definitions.hh>

class Projectile : public IDamager, public server::IEntity
{
private:
    server::hp_t damage;
    unsigned int nbHits;
public:
    Projectile(const server::entityId_t entityId);

    server::hp_t getDamage();
    void collide(server::IEntity *);

    server::EntityAction *nextAction();

};


#endif //CPP_RTYPE_PROJECTILE_HH
