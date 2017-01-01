//
// Created by lewis_e on 01/01/17.
//

#include <entities/Entity.hh>
#include "entities/VisualFx.hh"

using namespace server;

VisualFx::VisualFx(pos_t posX, pos_t posY, const std::string &sprite, const std::string &sound, int time, int x_offset,
                   int y_offset) :
    posX(posX), posY(posY), sprite(sprite), sound(sound), time(time), playedSound(false), x_offset(x_offset), y_offset(y_offset)
{ }

server::Tribool VisualFx::collidesWith(const server::Entity &entity)
{
    return NA;
}

void VisualFx::collide(const server::Entity &entity, server::round_t)
{
    return;
}

server::EntityAction *VisualFx::act(server::round_t current_round, const server::Grid &)
{
    EntityAction * act = new EntityAction();

    if (!playedSound)
    {
        if (current_round % POWERUP_SPAWN_FREQUENCY == 0)
            act->newEntity = new PowerUp(data->getPosX() + 50, data->getPosY() - y_offset + 50);
        act->soundToPlay = sound;
        playedSound = true;
    }
    if (current_round - startRound >= time)
    {
        act->destroy = true;
    }

    return (act);
}

server::EntityInitialization *VisualFx::initialize(server::round_t round, const server::Grid &environment)
{
    startRound = round;

    EntityInitialization * init = new EntityInitialization();
    init->posX = posX;
    init->posY = posY;
    init->sprite.path = sprite;
    init->team = NEUTRAL;

    return (init);
}

server::hp_t VisualFx::getDamage()
{
    return 0;
}





void VisualFx::PowerUp::collide(const server::Entity &entity, server::round_t current_round) {
    this->mustDestroy = true;
}

server::EntityAction *VisualFx::PowerUp::act(server::round_t current_round, const server::Grid &environment) {
    server::EntityAction *action = new server::EntityAction();

    action->destroy = this->mustDestroy;
    action->speedX = -1;
    return action;
}

server::EntityInitialization *VisualFx::PowerUp::initialize(server::round_t round, const server::Grid &environment) {
    server::EntityInitialization *initialization = new server::EntityInitialization();
    this->mustDestroy = false;
    initialization->action.speedX = -1.5f;
    initialization->sprite.sizeX = 24;
    initialization->sprite.sizeY = 24;
    initialization->team = server::Team::NEUTRAL;
    initialization->sprite.path = "media/sprites/powerupA.png";
    initialization->posX = posX;
    initialization->posY = posY;
    return initialization;
}

server::hp_t VisualFx::PowerUp::getDamage() {
    return -200;
}

server::Tribool VisualFx::PowerUp::collidesWith(const server::Entity &entity) {
    return entity.data.getTeam() && entity.data.getHp() > 0 ? server::T_TRUE : server::NA;
}

VisualFx::PowerUp::PowerUp(pos_t posX, pos_t posY)
{
    this->posX = posX;
    this->posY = posY;
}
