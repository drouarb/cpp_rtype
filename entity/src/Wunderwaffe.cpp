//
// Created by greg on 30/12/16.
//

#include "Wunderwaffe.hh"

void Wunderwaffe::collide(const server::Entity &entity, server::round_t) {

}

server::EntityAction *Wunderwaffe::act(server::round_t current_round, const std::vector<server::Entity *> &vector) {
    server::EntityAction *action = new server::EntityAction();

    action->destroy = false;
    action->hp = DEFAULT_LIFE;

    if (current_round % 2 == 0) {
        //TODO add bullet
    }

    if (current_round % 10 * 30) {
        //TODO add BIG BULLET
    }

    return action;
}

server::EntityInitialization *
Wunderwaffe::initialize(server::round_t round, const std::vector<server::Entity *> &vector) {
    return nullptr;
}

server::hp_t Wunderwaffe::getDamage() {
    return DEFAULT_DAMAGE;
}

server::Tribool Wunderwaffe::collidesWith(const server::Entity &entity) {
    return server::T_TRUE;
}
