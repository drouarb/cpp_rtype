//
// Created by greg on 02/12/2016.
//

#include <definitions.hh>
#include <Player.hh>
#include <iostream>
#include <cmath>
#include "Entity.hh"

using namespace server;

void Player::shoot(attackId_t) {
    //TODO Create map of <attackId_t, ADynamicObject *>
    this->attackQueue.push(new MagicMissile(this->data->getPosX() + 105, this->data->getPosY()));
}

Player::Player() : mustDestroy(0), vectX(0), vectY(0), newHp(0) {
    INFO("Player created")
}

void Player::collide(const Entity &entity, server::round_t current_round) {
    INFO("Collide test")
    if (entity.data.getTeam() == server::Team::PLAYER) {
        return;
    }
    std::cout << "Player " << this->data->getId() << " collides with player id " << entity.data.getId() << std::endl;
    this->newHp = entity.obj->getDamage();
}

EntityAction *Player::act(round_t current_round) {
//    while (!attackQueue.empty()) {
//        attackQueue.pop();
//    }
    INFO("Player hp: " << this->data->getHp())
    EntityAction *act = new EntityAction();
    if (!attackQueue.empty()) {
        ADynamicObject *&pObject = attackQueue.front();
        act->newEntity = pObject;
        attackQueue.pop();
        INFO("PLayer " << this->data->getId() << " : BOUM /!\\")
    }
    if ((mustDestroy && mustDestroy + 1 == current_round) || this->data->getHp() <= 0) {
        INFO("PLayer " << this->data->getId() << " : DED /!\\")
        act->destroy = true;
    }
    act->speedX = vectX;
    act->speedY = vectY;
    act->hp = this->data->getHp() - this->newHp;

    this->newHp = 0;
    return act;
}

EntityInitialization *Player::initialize() {
    EntityInitialization *ei = new EntityInitialization();
    ei->team = PLAYER;
    ei->action.hp = 5;
    ei->posX = 0;
    ei->posY = FIELD_HEIGHT / 2;
    ei->sprite.sizeX = 400;
    ei->sprite.sizeY = 400;
    ei->action.hp = DEFAULT_LIFE;
    ei->sprite.path = "media/references/e_100.png";

    this->newHp = 0;
    return (ei);
}

hp_t Player::getDamage() {
    return (0);
}

void Player::move(speed_t vectX, speed_t vectY) {
    this->vectX = vectX;
    this->vectY = vectY;
}

bool Player::collideWith(const Entity &) {
    return true;
}

void Player::MagicMissile::collide(const Entity &entity, server::round_t current_round) {
    if (entity.data.getTeam() == server::Team::PLAYER) {
        INFO("MagicMissile collide with PLAYERRRRRR " << entity.data.getId())
        INFO("PLAYER POS {x: " << entity.data.getPosX() << ", y:" << entity.data.getPosY());
        INFO("MISSILE POS {x: " << this->data->getPosX() << ", y:" << this->data->getPosY());
        return;
    }
    INFO("MagicMissile collide with : " << entity.data.getId() << "(id: " << this->data->getId() << ")")
    this->mustDestroy = current_round;
}

EntityAction *Player::MagicMissile::act(round_t current_round) {
    server::EntityAction *entityAction = new server::EntityAction();

    if (this->mustDestroy != 0 && this->mustDestroy + 1 == current_round) {
        entityAction->destroy = true;
        INFO("MagicMassile ded" << this->data->getId() << ", x:" << this->data->getPosX() << ", y: "
                                << this->data->getPosY())
    }
/*
    auto circle_speed = 2;
    auto x_speed = 2;
    auto rad = (current_round % 31) * 0.2;
    auto vectX = cos(rad) * circle_speed + x_speed;
    auto vectY = sin(rad) * circle_speed;
    entityAction->speedX = static_cast<speed_t >(vectX);
    entityAction->speedY = static_cast<speed_t >(vectY);
  */
    entityAction->speedX = 3;
    entityAction->speedY = 0;
    return entityAction;
}

EntityInitialization *Player::MagicMissile::initialize() {
    EntityInitialization *initialization = new EntityInitialization();
    initialization->action.hp = DEFAULT_LIFE;
    initialization->posX = this->posX;
    initialization->posY = this->posY;
    initialization->team = server::Team::PLAYER;
    initialization->sprite.sizeX = 50;
    initialization->sprite.sizeY = 50;
    initialization->sprite.path = "media/sprites/magicBullet.png";
    return initialization;
}

hp_t Player::MagicMissile::getDamage() {
    return DAMAGE;
}

Player::MagicMissile::MagicMissile(pos_t posX, pos_t posY) : mustDestroy(0), posX(posX), posY(posY) {}

bool Player::MagicMissile::collideWith(const Entity &entity) {
    return entity.data.getTeam() != server::Team::PLAYER;
}

void Player::CirclingMissile::collide(const server::Entity &entity, server::round_t current_round) {
    if (entity.data.getTeam() == server::Team::PLAYER) {
        INFO("CirclingMissile collide with PLAYERRRRRR " << entity.data.getId())
        INFO("PLAYER POS {x: " << entity.data.getPosX() << ", y:" << entity.data.getPosY());
        INFO("MISSILE POS {x: " << this->data->getPosX() << ", y:" << this->data->getPosY());
        return;
    }
    INFO("CirclingMissile collide with : " << entity.data.getId() << "(id: " << this->data->getId() << ")")
    this->mustDestroy = current_round;
}

EntityAction *Player::CirclingMissile::act(round_t current_round) {
    server::EntityAction *entityAction = new server::EntityAction();

    if (this->mustDestroy != 0 && this->mustDestroy + 1 == current_round) {
        entityAction->destroy = true;
        INFO("CirclingMissile ded" << this->data->getId() << ", x:" << this->data->getPosX() << ", y: "
                                   << this->data->getPosY())
    }
    entityAction->speedX = 10;
    entityAction->speedY = 0;
    return entityAction;
}

EntityInitialization *Player::CirclingMissile::initialize() {
    return nullptr;
}

hp_t Player::CirclingMissile::getDamage() {
    return DAMAGE;
}

bool Player::CirclingMissile::collideWith(const Entity &entity) {
    return entity.data.getTeam() != server::Team::PLAYER;
}
