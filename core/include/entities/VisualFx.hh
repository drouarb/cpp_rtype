//
// Created by lewis_e on 01/01/17.
//

#ifndef CPP_RTYPE_VISUALFX_HH
#define CPP_RTYPE_VISUALFX_HH

#include "ADynamicObject.hh"
#include "../Definitions.hh"
#include <string>

#define POWERUP_SPAWN_FREQUENCY 3

namespace server
{
    class VisualFx : public ADynamicObject
    {
    public:
        enum y_offset
        {
            Y_EXPLOSION_A = -20,
            Y_EXPLOSION_B = -120,
            Y_EXPLOSION_C = -120
        };

        VisualFx(pos_t posX, pos_t posY, const std::string &sprite, const std::string &sound, int time, int x_offset,
                         int y_offset);

        server::Tribool collidesWith(const server::Entity &entity) override;
        void collide(const server::Entity &entity, server::round_t current_round) override;
        server::EntityAction *act(server::round_t current_round, const server::Grid &) override;
        server::EntityInitialization *initialize(server::round_t, const server::Grid &environment) override;
        server::hp_t getDamage() override;

    private:
        pos_t posX;
        pos_t posY;
        std::string sprite;
        std::string sound;
        int time;
        round_t startRound;
        bool playedSound;
        pos_t x_offset;
        pos_t y_offset;

    public:

        class PowerUp : public server::ADynamicObject {
        private:
            bool mustDestroy;
            pos_t posX;
            pos_t posY;

        public:
            PowerUp(pos_t posX, pos_t posY);
            PowerUp();

            void collide(const server::Entity &entity, server::round_t current_round) override;

            server::EntityAction *act(server::round_t current_round, const server::Grid &environment) override;

            server::EntityInitialization *initialize(server::round_t round, const server::Grid &environment) override;

            server::hp_t getDamage() override;

            server::Tribool collidesWith(const server::Entity &entity) override;
        };
    };
}

#endif //CPP_RTYPE_VISUALFX_HH
