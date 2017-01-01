//
// Created by greg on 02/12/2016.
//

#include <Definitions.hh>
#include <entities/Player.hh>
#include <iostream>
#include "entities/Entity.hh"


using namespace server;

Player::Player() : mustDestroy(false), vectX(0), vectY(0), lostHp(0), nextAttack(NOATTACK) {
    INFO("Player created")
    score = 0;
}

void Player::shoot(round_t current_round, attackId_t attack)
{
    nextAttack = attack;
}

void Player::collide(const Entity &entity, server::round_t current_round) {
    INFO("Collide test")
    if (entity.data.getTeam() == server::Team::PLAYER)
    {
        return;
    }
    this->lostHp += entity.obj->getDamage();
}

EntityAction *Player::act(round_t current_round, const Grid &) {
    cleanAttackTimeline(current_round);
    INFO("Player hp: " << this->data->getHp())
    EntityAction *act = new EntityAction();
    if (nextAttack != NOATTACK && attackTimeline.find(current_round) == attackTimeline.end()) {
        act->newEntity = this->createAttack(nextAttack, current_round);
        nextAttack = NOATTACK;
        INFO("PLayer " << this->data->getId() << " : BOUM /!\\")
    }
    if (mustDestroy)
    {
        INFO("PLayer " << this->data->getId() << " : DED /!\\")
        act->destroy = true;
    }
    if (data->getHp() <= 0)
    {
        INFO("PLayer " << this->data->getId() << " : FALLING /!\\")
        vectX = 0;
        vectY = 20;
    }
    act->speedX = vectX;
    act->speedY = vectY;

    if (data->getHp() > 0)
        act->hp = this->data->getHp() - this->lostHp;
    this->lostHp = 0;

    this->lastRound = current_round;
    return act;
}

EntityInitialization *Player::initialize(round_t, const Grid &)
{
    EntityInitialization *ei = new EntityInitialization();
    ei->team = PLAYER;
    ei->action.hp = 5;
    ei->sprite.sizeX = 50;
    ei->sprite.sizeY = 50;
    ei->posX = ei->sprite.sizeX;
    ei->posY = FIELD_HEIGHT / 2;
    ei->action.hp = DEFAULT_LIFE;
    ei->sprite.path = "media/sprites/magicalGirlD.png";

    this->lostHp = 0;
    return (ei);
}

hp_t Player::getDamage() {
    return (0);
}

void Player::move(speed_t vectX, speed_t vectY) {
    this->vectX = vectX;
    this->vectY = vectY;
}

Tribool Player::collidesWith(const Entity &entity)
{
    if (data->getHp() <= 0)
        return server::NA;
    return (entity.data.getTeam() != server::Team::PLAYER ? T_TRUE : T_FALSE);
}

void Player::cleanAttackTimeline(server::round_t round)
{
    //manage rewind
    round_t first = lastRound - (TIMELINE_LENGTH - 1);
    if (first < 0)
        first = 0;
    round_t r = lastRound;
    while (r > round && r >= first)
    {
        while (r >= first && attackTimeline[r] != NOATTACK)
        {
            attackTimeline.erase(r);
            --r;
        }
    }

    //remove old ones
    if (lastRound >= TIMELINE_LENGTH)
    {
        attackTimeline.erase(lastRound - TIMELINE_LENGTH);
    }
}

ADynamicObject * Player::createAttack(attackId_t id, round_t round)
{
    setAttackWait(id, BASIC_MISSILE_TIME, round);
    return new MagicMissile(this, this->data->getPosX() + CIRCLE_RADIUS * 2 + BULLET_SIZE + 1, this->data->getPosY(),
                            round, "media/sprites/crystalA.png");
}

void Player::setAttackWait(attackId_t id, round_t nbRounds, round_t currentRound)
{
    attackTimeline[currentRound] = 0;
    for (int i = 1; i < nbRounds; ++i)
        attackTimeline[currentRound + i] = NOATTACK;
}


/*
 * ----------------------------------------------------------------------------------------------
 */

Player::BasicMissile::BasicMissile(APlayer * owner, pos_t posX, pos_t posY, const std::string &sprite) :
        Power(owner), posX(posX), posY(posY), sprite(sprite) {}

EntityInitialization *Player::BasicMissile::initialize(round_t, const server::Grid &environment) {
    this->mustDestroy = false;
    EntityInitialization *initialization = new server::EntityInitialization;
    initialization->posY = this->posY;
    initialization->posX = this->posX;
    initialization->sprite = this->sprite;
    initialization->action.speedX = 25;
    initialization->action.speedY = 0;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = 21;
    initialization->sprite.sizeY = 11;
    return initialization;
}

void Player::BasicMissile::collide(const server::Entity &entity, server::round_t)
{
    if (entity.data.getTeam() == FOE)
    {
        modScore(static_cast<score_t >(getDamage()));
    }
    this->mustDestroy = true;
}

EntityAction *Player::BasicMissile::act(round_t current_round, const server::Grid &environment) {
    EntityAction *action = new server::EntityAction();
    action->speedX = 25;
    action->speedY = 0;
    action->destroy = this->mustDestroy;
    return action;
}

hp_t Player::BasicMissile::getDamage() {
    return 30;
}

Tribool Player::BasicMissile::collidesWith(const Entity &entity) {
    return (entity.data.getTeam() == server::PLAYER ? T_FALSE : T_TRUE);
}
