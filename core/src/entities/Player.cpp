//
// Created by greg on 02/12/2016.
//

#include <Definitions.hh>
#include <entities/Player.hh>
#include <iostream>
#include <cmath>
#include "entities/Entity.hh"
#include "../../../server/include/Grid.hh"


using namespace server;

Player::Player() : mustDestroy(0), vectX(0), vectY(0), lostHp(0), nextAttack(NOATTACK) {
    INFO("Player created")
}

void Player::shoot(round_t current_round) {
    //TODO Create map of <attackId_t, ADynamicObject *>
    nextAttack = 0;
}

void Player::collide(const Entity &entity, server::round_t current_round) {
    INFO("Collide test")
    if (entity.data.getTeam() == server::Team::PLAYER) {
        return;
    }
    std::cout << "Player " << this->data->getId() << " collides with player id " << entity.data.getId() << std::endl;
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
    if ((mustDestroy && mustDestroy + 1 == current_round) || this->data->getHp() <= 0) {
        INFO("PLayer " << this->data->getId() << " : DED /!\\")
        act->destroy = true;
    }
    act->speedX = vectX;
    act->speedY = vectY;
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

Tribool Player::collidesWith(const Entity &entity) {
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
    setAttackWait(id, 3, round);
    return new MagicMissile(this->data->getPosX() + CIRCLE_RADIUS * 2 + BULLET_SIZE + 1, this->data->getPosY(), round);
}

void Player::setAttackWait(attackId_t id, round_t nbRounds, round_t currentRound)
{
    attackTimeline[currentRound] = 0;
    for (int i = 1; i < nbRounds; ++i)
        attackTimeline[currentRound + i] = NOATTACK;
}


Player::MagicMissile::MagicMissile(pos_t posX, pos_t posY, round_t startRound) : mustDestroy(0), posX(posX), posY(posY)
{ }


void Player::MagicMissile::collide(const Entity &entity, server::round_t current_round) {
    INFO("MagicMissile collide with : " << entity.data.getId() << "(id: " << this->data->getId() << ")")
    this->mustDestroy = true;
}

EntityAction *Player::MagicMissile::act(round_t current_round, const server::Grid &)
{
    server::EntityAction *entityAction = new server::EntityAction();

    if (this->mustDestroy) {
        entityAction->destroy = true;
        INFO("MagicMassile ded" << this->data->getId() << ", x:" << this->data->getPosX() << ", y: "
                                << this->data->getPosY())
    }
    auto circle_speed = CIRCLE_RADIUS;
    auto x_speed = 5;
    auto rad = ((current_round - startRound) % 15) * 0.4;
    auto vectX = cos(rad) * circle_speed + x_speed;
    auto vectY = sin(rad) * circle_speed;
    entityAction->speedX = static_cast<speed_t >(vectX);
    entityAction->speedY = static_cast<speed_t >(vectY);

/*
    entityAction->speedX = 5;
    entityAction->speedY = 0;
*/

    return entityAction;
}

EntityInitialization *Player::MagicMissile::initialize(round_t round, const Grid &environment)
{
    EntityInitialization *initialization = new EntityInitialization();
    initialization->action.hp = DEFAULT_LIFE;
    initialization->posX = this->posX;
    initialization->posY = this->posY;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = BULLET_SIZE;
    initialization->sprite.sizeY = BULLET_SIZE;
    initialization->sprite.path = "media/sprites/magicBullet.png";
    this->startRound = round;
    return initialization;
}

hp_t Player::MagicMissile::getDamage() {
    return DAMAGE;
}

Tribool Player::MagicMissile::collidesWith(const Entity &entity) {
    return (entity.data.getTeam() != server::Team::PLAYER ? T_TRUE : T_FALSE);
}
