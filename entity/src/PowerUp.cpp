//
// Created by greg on 01/01/17.
//

#include <entities/Entity.hh>
#include "PowerUp.hh"

void PowerUp::collide(const server::Entity &entity, server::round_t current_round) {
    this->mustDestroy = true;
}

server::EntityAction *PowerUp::act(server::round_t current_round, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    action->destroy = this->mustDestroy;
    action->speedX = -1;
    return action;
}

server::EntityInitialization *PowerUp::initialize(server::round_t round, const server::Grid &environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    this->mustDestroy = false;
    initialization->action.speedX = -1.5f;
    initialization->sprite.sizeX = 24;
    initialization->sprite.sizeY = 24;
    initialization->team = server::Team::NEUTRAL;
    initialization->sprite.path = "media/sprites/powerupA.png";
    return initialization;
}

server::hp_t PowerUp::getDamage() {
    return -200;
}

server::Tribool PowerUp::collidesWith(const server::Entity &entity) {
    return entity.data.getTeam() && entity.data.getHp() > 0 ? server::T_TRUE : server::NA;
}


extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new PowerUp());
}
}
