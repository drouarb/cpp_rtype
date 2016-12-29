#pragma once

#include "Definitions.hh"
#include "entities/Player.hh"

namespace server {
    class Controller {
    private:
        server::APlayer *player;
        server::Entity *entity;

    public:
        void playMove(pos_t speedX, pos_t speedY);

        void playShoot(attackId_t attackId, round_t tick);

        void setEntity(Player *entity);

        void destroy();

        Entity *getEntity() const;

        void setEntity(Entity *entity);
    };
}