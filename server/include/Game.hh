#ifndef RTYPE_GAME_HH_
#define RTYPE_GAME_HH_

#include "Level.hh"

namespace server
{
    class Game
    {
    public:
        Game();
        Game(const Level &);
        ~Game();

        void setLevel(const Level &);
        void tick(round_t);

    private:
        const Level * lvl;
        std::vector<IEntity*> entities;
        round_t round;

        void progressLevel();
        void checkCollisions();
        void letEntitesAct();
        void moveEntities();
    };
}

#endif