//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_AACTOR_HH
#define CPP_RTYPE_AACTOR_HH


#include <vector>
#include "Attack.hh"
#include "IEntity.hh"

namespace Server {

    class AActor : public Server::AEntity {
    public:
        AActor(const Server::EntityId entityId, const std::string &sprite);

        virtual void play(std::vector<Server::IEntity *>)= 0;

        virtual void hit(int damage);
    };

}

#endif //CPP_RTYPE_AACTOR_HH
