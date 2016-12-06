//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_IDAMAGER_HH
#define CPP_RTYPE_IDAMAGER_HH

#include "definitions.hh"
#include <IEntity.hh>

class IDamager {

public:
    virtual server::damage_t getDamage()= 0;

};

#endif //CPP_RTYPE_IDAMAGER_HH
