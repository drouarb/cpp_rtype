//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_PLAYER_HH
#define CPP_RTYPE_PLAYER_HH

#include <queue>
#include "APlayer.hh"

namespace server {
    class Player : public APlayer {
    private:

        static const int DEFAULT_LIFE = 500;

        //        std::queue<attackId_t> __attribute__((deprecated)) attackQueue;
        std::queue<ADynamicObject *> attackQueue;
        round_t mustDestroy;
        speed_t vectX;
        speed_t vectY;
        hp_t newHp;

    public:

        Player();

        void shoot(attackId_t attackId) override;

        void move(speed_t vectX, speed_t vectY) override;

        bool collideWith(const Entity &entity) override;

        void collide(const Entity &entity, server::round_t current_round) override;

        EntityAction *act(round_t round) override;

        EntityInitialization *initialize() override;

        hp_t getDamage() override;

        class MagicMissile : public ADynamicObject {
        public:
            void collide(const Entity &entity, server::round_t current_round) override;

            EntityAction *act(round_t current_round) override;

            EntityInitialization *initialize() override;

            hp_t getDamage() override;

            MagicMissile(pos_t posX, pos_t posY);

            bool collideWith(const Entity &entity) override;

        private:
            round_t mustDestroy;

            pos_t posX;
            pos_t posY;
            static const int DAMAGE = 20;

        };

        class CirclingMissile : public ADynamicObject {
        public:
            void collide(const server::Entity &entity, server::round_t current_round) override;

            EntityAction *act(round_t current_round) override;

            EntityInitialization *initialize() override;

            hp_t getDamage() override;

            bool collideWith(const Entity &entity) override;

        private:
            static const int DAMAGE = 100;
            round_t mustDestroy;
        };
    };
}

#endif //CPP_RTYPE_PLAYER_HH
