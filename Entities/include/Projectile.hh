//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_PROJECTILE_HH
#define CPP_RTYPE_PROJECTILE_HH


#include <AEntity.hh>
#include "IDamager.hh"

class Projectile : public IDamager {
private:
    damagePoint_t damage;
    unsigned int nbHits;
public:
    Projectile(const Server::EntityId entityId);

    damagePoint_t getDamage();
    void collide(Server::IEntity *);

    Server::EntityAction *nextAction();

};


#endif //CPP_RTYPE_PROJECTILE_HH
