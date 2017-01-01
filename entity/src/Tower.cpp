//
// Created by greg on 01/01/17.
//

#include <entities/Entity.hh>
#include "Tower.hh"




void Tower::collide(const server::Entity &entity, server::round_t current_round) {

}

server::EntityAction *Tower::act(server::round_t, const server::Grid &environment) {
    server::EntityAction *entityAction;

    entityAction = new server::EntityAction();
    return entityAction;
}

server::EntityInitialization *Tower::initialize(server::round_t round, const server::Grid &environment) {
    server::EntityInitialization *entityInitialization = new server::EntityInitialization();
    entityInitialization->sprite.path = "media/sprites/tower.png";
    entityInitialization->sprite.sizeX = 156;
    entityInitialization->sprite.sizeY = 463;
    return entityInitialization;
}

server::hp_t Tower::getDamage() {
    return 31000;
}

server::Tribool Tower::collidesWith(const server::Entity &entity) {
    return entity.data.getTeam() == server::Team::PLAYER ? server::T_TRUE : server::NA;
}

extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new Tower());
}
}