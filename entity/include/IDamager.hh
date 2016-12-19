//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_IDAMAGER_HH
#define CPP_RTYPE_IDAMAGER_HH

#include "Definitions.hh"

class IDamager {

public:
    virtual server::hp_t getDamage()= 0;

};

#endif //CPP_RTYPE_IDAMAGER_HH
