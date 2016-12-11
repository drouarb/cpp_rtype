#pragma once

#include "definitions.hh"
#include "IEntity.hh"
#include "IPlayer.hh"
#include "Player.hh"

namespace server {
    class Controller {
    private:
        server::Player *entity;

    public:
        void playMove(pos_t speedX, pos_t speedY);
        void playShoot(attackId_t attackId);
        void setEntity(Player *entity);
        void destroy(); //TODO: the player's entity must return destroy=true in the next entityAction

    private:
        IPlayer *getPlayer();
    };
}