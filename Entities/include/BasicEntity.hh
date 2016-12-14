//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_BASICENTITY_HH
#define CPP_RTYPE_BASICENTITY_HH


#include <ostream>
#include "../../server/include/entities/ADynamicObject.hh"
#include "../../server/include/definitions.hh"

class BasicEntity : public server::ADynamicObject {
public:
    BasicEntity();

    friend std::ostream &operator<<(std::ostream &os, const BasicEntity &entity);

    void collide(server::IEntity *) final;
    server::EntityAction *nextAction() final;
    server::EntityInitialization *initialize() final;
};



#endif //CPP_RTYPE_BASICENTITY_HH
