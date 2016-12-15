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

//        std::queue<attackId_t> __attribute__((deprecated)) attackQueue;
        std::queue<ADynamicObject *>  attackQueue;
        bool mustDestroy;
        speed_t vectX;
        speed_t vectY;

    protected:

        class MagicMissile : public ADynamicObject {
        public:
            void collide(const Entity &entity) override;

            EntityAction *nextAction() override;

            EntityInitialization *initialize() override;

            damage_t getDamage() override;

            MagicMissile();

        private:
            bool mustDestroy;

            static const int DAMAGE = 20;

        };

    public:

        Player();
        void shoot(attackId_t attackId) override;
        void move(speed_t vectX, speed_t vectY) override;


        void collide(const Entity &entity) override;
        EntityAction *nextAction() override;
        EntityInitialization * initialize() override;
        damage_t getDamage() override;
    };
}

#endif //CPP_RTYPE_PLAYER_HH
