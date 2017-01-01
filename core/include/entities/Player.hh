//
// Created by greg on 02/12/2016.
//

#ifndef CPP_RTYPE_PLAYER_HH
#define CPP_RTYPE_PLAYER_HH

#include "APlayer.hh"
#include "Definitions.hh"
#include <map>

namespace server {
    class Player : public APlayer {
    private:

        static const int DEFAULT_LIFE = 500;
        static const int CIRCLE_RADIUS = 15;
        static const int TIMELINE_LENGTH = 60;

        bool mustDestroy;
        speed_t vectX;
        speed_t vectY;
        hp_t lostHp;

        /**
         * Must be called before doing anything in act().
         */
        void cleanAttackTimeline(server::round_t round);


    protected:
        static const int BULLET_SIZE = 25;
        static const int BASIC_MISSILE_TIME = 8;

        std::map<server::round_t, server::attackId_t> attackTimeline;
        round_t lastRound;
        attackId_t nextAttack;

        void setAttackWait(attackId_t id, round_t nbRounds, round_t currentRound);
        virtual ADynamicObject * createAttack(attackId_t id, round_t round);

        class BasicMissile : public ADynamicObject, private Player::Power
        {
        private:
            bool mustDestroy;
            pos_t posX;
            pos_t posY;
            std::string sprite;
        public:
            BasicMissile(APlayer * owner, pos_t posX, pos_t posY, const std::string &sprite);

            void collide(const server::Entity &entity, server::round_t current_round) override;

            EntityAction *act(round_t current_round, const server::Grid &environment) override;

            EntityInitialization *initialize(round_t round, const server::Grid &environment) override;

            hp_t getDamage() override;

            Tribool collidesWith(const Entity &entity) override;
        };

    public:

        Player();

        void shoot(round_t attackId, attackId_t attack) override;
        void move(speed_t vectX, speed_t vectY) override;
        Tribool collidesWith(const Entity &entity) override;
        void collide(const Entity &entity, server::round_t current_round) override;
        EntityAction *act(round_t round, const Grid &) override;
        EntityInitialization *initialize(round_t, const Grid &) override;
        hp_t getDamage() override;

        class MagicMissile : public ADynamicObject, protected APlayer::Power {
        public:
            MagicMissile(APlayer *owner, pos_t posX, pos_t posY, round_t startRound, const std::string & sprite);

            void collide(const Entity &entity, server::round_t current_round) override;
            EntityAction *act(round_t current_round, const Grid &) override;
            EntityInitialization *initialize(round_t, const Grid &environment) override;
            hp_t getDamage() override;
            Tribool collidesWith(const Entity &entity) override;

        private:
            bool mustDestroy;
            round_t startRound;
            std::string sprite;

            pos_t posX;
            pos_t posY;
            static const int DAMAGE = 15;
        };
    };
}

#endif //CPP_RTYPE_PLAYER_HH
