//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_BASICENTITY_HH
#define CPP_RTYPE_BASICENTITY_HH


#include "AEntity.hh"

class BasicEntity : public Server::AEntity {
public:
    BasicEntity(const Server::EntityId entityId);

    virtual void collide(Server::IEntity *) final;
    virtual Server::EntityAction *nextAction() final;
};

#endif //CPP_RTYPE_BASICENTITY_HH
