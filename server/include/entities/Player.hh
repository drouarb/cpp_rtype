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

        std::queue<attackId_t> attackQueue;
        round_t mustDestroy;
        speed_t vectX;
        speed_t vectY;
        hp_t newHp;

    public:

        Player();

        void shoot(attackId_t attackId) override;
        void move(speed_t vectX, speed_t vectY) override;
        Tribool collidesWith(const Entity &entity) override;
        void collide(const Entity &entity, server::round_t current_round) override;
        EntityAction *act(round_t round, const std::vector<Entity *> &) override;
        EntityInitialization *initialize() override;
        hp_t getDamage() override;

        class MagicMissile : public ADynamicObject {
        public:
            MagicMissile(pos_t posX, pos_t posY, round_t startRound);

            void collide(const Entity &entity, server::round_t current_round) override;
            EntityAction *act(round_t current_round, const std::vector<Entity *> &) override;
            EntityInitialization *initialize() override;
            hp_t getDamage() override;
            Tribool collidesWith(const Entity &entity) override;

        private:
            round_t mustDestroy;
            round_t startRound;

            pos_t posX;
            pos_t posY;
            static const int DAMAGE = 20;

        };
    };
}

#endif //CPP_RTYPE_PLAYER_HH
