//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_POWERUP_HH
#define CPP_RTYPE_POWERUP_HH


#include <AEntity.hh>

class PowerUp : public Server::AEntity {
public:
    PowerUp(const Server::EntityId entityId);

    void collide(Server::IEntity *);

    Server::EntityAction *nextAction();

};


#endif //CPP_RTYPE_POWERUP_HH
