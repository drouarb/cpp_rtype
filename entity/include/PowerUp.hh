//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_POWERUP_HH
#define CPP_RTYPE_POWERUP_HH


#include <IEntity.hh>

class PowerUp : public server::IEntity {
public:
    PowerUp(const server::entityId_t entityId);

    void collide(server::IEntity *);

    server::EntityAction *nextAction();

};


#endif //CPP_RTYPE_POWERUP_HH
