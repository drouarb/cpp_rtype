//
// Created by greg on 30/12/16.
//

#include <iostream>
#include "Obstacle.hh"

void Obstacle::collide(const server::Entity &entity, server::round_t) {
}

server::EntityAction *Obstacle::act(server::round_t, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    action->speedX = 0;
    action->speedY = 0;
    return action;
}

server::EntityInitialization *Obstacle::initialize(server::round_t, const server::Grid &environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    initialization->sprite.sizeX = BORDER_OBSTACLE_SIZE;
    initialization->sprite.sizeY = 1;
    initialization->team = server::Team::NEUTRAL;
    initialization->action.destroy = false;
    initialization->action.hp = 0;
    initialization->sprite.path = "";
    return initialization;
}

server::hp_t Obstacle::getDamage() {
    return 0;
}

server::Tribool Obstacle::collidesWith(const server::Entity &entity) {
    return server::T_TRUE;
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new Obstacle());
}
}
