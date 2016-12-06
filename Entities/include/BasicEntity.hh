//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_BASICENTITY_HH
#define CPP_RTYPE_BASICENTITY_HH


#include "IEntity.hh"

class BasicEntity : public server::IEntity {
public:
    BasicEntity(const server::entityId_t entityId);

    virtual void collide(server::IEntity *) final;
    virtual server::EntityAction *nextAction() final;
};



#endif //CPP_RTYPE_BASICENTITY_HH
