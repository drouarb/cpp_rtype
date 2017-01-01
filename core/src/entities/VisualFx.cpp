//
// Created by lewis_e on 01/01/17.
//

#include "entities/VisualFx.hh"

using namespace server;

VisualFx::VisualFx(pos_t posX, pos_t posY, const std::string &sprite, const std::string &sound, int time) :
    posX(posX), posY(posY), sprite(sprite), sound(sound), time(time), playedSound(false)
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

