//
// Created by greg on 02/12/2016.
//

#include <definitions.hh>
#include <Player.hh>
#include <iostream>
#include "Entity.hh"

using namespace server;

void Player::shoot(attackId_t) {
    //TODO Create map of <attackId_t, ADynamicObject *>
    this->attackQueue.push(new MagicMissile());
}

Player::Player() : mustDestroy(false), vectX(0), vectY(0) {}

void Player::collide(const Entity &entity) {
    std::cout << "Player " << this->data->getId() << " collides with entity id " << entity.data.getId() << std::endl;
}

EntityAction *Player::nextAction() {
//    while (!attackQueue.empty()) {
//        attackQueue.pop();
//    }
    EntityAction *act = new EntityAction();
    if (!attackQueue.empty()) {
        ADynamicObject *&pObject = attackQueue.back();
        act->newEntity = pObject;
        attackQueue.pop();
    }
    if (mustDestroy) {
        act->destroy = true;
    }
    act->speedX = vectX;
    act->speedY = vectY;    
    return act;
}

EntityInitialization *Player::initialize() {
    EntityInitialization *ei = new EntityInitialization();
    ei->team = PLAYER;
    ei->action.hp = 5;
    ei->posX = 0;
    ei->posY = FIELD_HEIGHT / 2;

    return (ei);
}

damage_t Player::getDamage() {
    return (0);
}

void Player::move(speed_t vectX, speed_t vectY) {
    this->vectX = vectX;
    this->vectY = vectY;
}

void Player::MagicMissile::collide(const Entity &) {
    this->mustDestroy = true;
}

EntityAction *Player::MagicMissile::nextAction() {
    server::EntityAction *entityAction = new server::EntityAction();

    if (this->mustDestroy) {
        entityAction->destroy = true;
        return entityAction;
    }
    return nullptr;
}

EntityInitialization *Player::MagicMissile::initialize() {
    return new EntityInitialization();
}

damage_t Player::MagicMissile::getDamage() {
    return DAMAGE;
}

Player::MagicMissile::MagicMissile() : mustDestroy(false) {}
