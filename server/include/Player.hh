//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_PLAYER_HH
#define CPP_RTYPE_PLAYER_HH

#include <queue>
#include "definitions.hh"
#include "IPlayer.hh"
#include "IEntity.hh"

namespace server {
    class Player : public IPlayer, public IEntity {
    private:
        server::entityId_t id;
        server::Team  team;
        std::string sprite;
        server::pos_t posX;
        server::pos_t posY;
        server::speed_t speedX;
        server::speed_t speedY;
        int hp;
        bool destroyed;

        std::queue<attackId_t> attackQueue;
        bool mustDestroy;

    public:
        Player();
        void shoot(attackId_t attackId) override;

        void setEntityId(entityId_t id) override;

        entityId_t getEntityId() override;

        Team getTeam() override;

        std::string &getSprite() override;

        void setPosX(pos_t pos) override;

        pos_t getPosX() override;

        void setPosY(pos_t pos) override;

        pos_t getPosY() override;

        void setSpeedX(speed_t speed) override;

        speed_t getSpeedX() override;

        void setSpeedY(speed_t speed) override;

        speed_t getSpeedY() override;

        void modHp(int i) override;

        int getHp() override;

        void destroy() override;

        void restore() override;

        bool isDestroyed() override;

        void collide(IEntity *entity) override;

        EntityAction *nextAction() override;


    };
}

#endif //CPP_RTYPE_PLAYER_HH
