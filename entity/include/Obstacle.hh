//
// Created by greg on 30/12/16.
//

#ifndef CPP_RTYPE_OBSTACLE_HH
#define CPP_RTYPE_OBSTACLE_HH


#include <entities/ADynamicObject.hh>

class Obstacle : public server::ADynamicObject {
public:
    void collide(const server::Entity &entity, server::round_t current_round) override;

    server::EntityAction *act(server::round_t current_round, const server::Grid &environment) override;

    server::EntityInitialization *initialize(server::round_t round, const server::Grid &environment) override;

    server::hp_t getDamage() override;

    server::Tribool collidesWith(const server::Entity &entity) override;
};


#endif //CPP_RTYPE_OBSTACLE_HH
