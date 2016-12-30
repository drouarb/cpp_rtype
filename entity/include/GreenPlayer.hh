//
// Created by greg on 22/12/16.
//

#ifndef CPP_RTYPE_GREENPLAYER_HH
#define CPP_RTYPE_GREENPLAYER_HH



#include <entities/Player.hh>
#include "../../server/include/Grid.hh"

class GreenPlayer : public server::Player {
protected:

    server::ADynamicObject * createAttack(server::attackId_t id, server::round_t round) override;

public:
    void shoot(server::round_t attackId) override;

    server::EntityInitialization *initialize(server::round_t round, const server::Grid &entity) override;

private:

    class WallAttack : public server::ADynamicObject {
    private:
        static const int DAMMAGE = 1;
        static const int DEFAULT_LIFE = 1;

        server::pos_t posX;
        server::pos_t posY;

        server::round_t initialRound;
        uint8_t layerLeft;
        enum {
            TOP,
            DOWN
        } nextPlace;


        class WallElement : public server::ADynamicObject {
        private:
            bool mustDestroy;
            server::pos_t posX;
            server::pos_t posY;

            static const int DEFAULT_DAMAGE = 1;
        public:
            WallElement(server::pos_t posX, server::pos_t posY);

            void collide(const server::Entity &entity, server::round_t current_round) override;

            server::EntityAction *
            act(server::round_t current_round, const server::Grid &vector) override;

            server::EntityInitialization *initialize(server::round_t round, const server::Grid &entity) override;

            server::hp_t getDamage() override;

            server::Tribool collidesWith(const server::Entity &entity) override;

        };

    public:

        WallAttack(server::pos_t posX, server::pos_t posY);

        void collide(const server::Entity &entity, server::round_t current_round) override;

        server::EntityAction *act(server::round_t current_round, const server::Grid &vector) override;

        server::EntityInitialization *initialize(server::round_t round, const server::Grid &entity) override;

        server::hp_t getDamage() override;

        server::Tribool collidesWith(const server::Entity &entity) override;
    };

};


#endif //CPP_RTYPE_GREENPLAYER_HH
