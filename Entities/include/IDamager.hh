//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_IDAMAGER_HH
#define CPP_RTYPE_IDAMAGER_HH

#include <AEntity.hh>

class IDamager : public Server::AEntity {

public:


    IDamager(const Server::EntityId entityId, const std::string &sprite) : AEntity(entityId, sprite) {}

    virtual damagePoint_t getDamage()= 0;

};

#endif //CPP_RTYPE_IDAMAGER_HH
