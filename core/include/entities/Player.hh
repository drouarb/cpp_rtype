//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_PLAYER_HH
#define CPP_RTYPE_PLAYER_HH

#include "APlayer.hh"
#include "Definitions.hh"
#include <queue>

namespace server {
    class Player : public APlayer {
    private:

        static const int DEFAULT_LIFE = 500;
        static const int MAX_ATTACK_QUEUE = 10;
        static const int CIRCLE_RADIUS = 15;
        static const int DEFAULT_PLAYER_SPEED = 1;

        round_t mustDestroy;
        speed_t vectX;
        speed_t vectY;
        hp_t newHp;

    protected:
        std::queue<ADynamicObject *> attackQueue;
        static const int BULLET_SIZE = 25;

    public:

        Player();

        void shoot(round_t attackId) override;
        void move(speed_t vectX, speed_t vectY) override;
        Tribool collidesWith(const Entity &entity) override;
        void collide(const Entity &entity, server::round_t current_round) override;
        EntityAction *act(round_t round, const Grid &) override;
        EntityInitialization *initialize(round_t, const Grid &) override;
        hp_t getDamage() override;

        class MagicMissile : public ADynamicObject {
        public:
            MagicMissile(pos_t posX, pos_t posY, round_t startRound);

            void collide(const Entity &entity, server::round_t current_round) override;
            EntityAction *act(round_t current_round, const Grid &) override;
            EntityInitialization *initialize(round_t, const Grid &environment) override;
            hp_t getDamage() override;
            Tribool collidesWith(const Entity &entity) override;

        private:
            bool mustDestroy;
            round_t startRound;

            pos_t posX;
            pos_t posY;
            static const int DAMAGE = 20;
        };
    };
}

#endif //CPP_RTYPE_PLAYER_HH
