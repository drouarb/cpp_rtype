//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_PLAYER_HH
#define CPP_RTYPE_PLAYER_HH

#include <queue>
#include "APlayer.hh"

namespace server
{
    class Player : public APlayer
    {
    private:

        std::queue<attackId_t> attackQueue;
        bool mustDestroy;
        speed_t vectX;
        speed_t vectY;

    public:

        Player();
        void shoot(attackId_t attackId) override;
        void move(speed_t vectX, speed_t vectY) override;


        void collide(const EntityData &entity) override;
        EntityAction *nextAction() override;
        EntityInitialization * initialize() override;

    };
}

#endif //CPP_RTYPE_PLAYER_HH
