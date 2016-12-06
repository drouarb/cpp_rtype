//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_OBSTACLE_HH
#define CPP_RTYPE_OBSTACLE_HH


#include <AEntity.hh>

class Obstacle : public server::AEntity {
public:
    Obstacle(const server::entityId_t entityId);

    void collide(server::IEntity *);

    server::EntityAction *nextAction();
};


#endif //CPP_RTYPE_OBSTACLE_HH
