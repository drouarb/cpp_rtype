//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_OBSTACLE_HH
#define CPP_RTYPE_OBSTACLE_HH


#include <AEntity.hh>

class Obstacle : Server::AEntity {
public:
    Obstacle(const Server::EntityId entityId);

    void collide(Server::IEntity *);

    Server::EntityAction *nextAction();
};


#endif //CPP_RTYPE_OBSTACLE_HH
