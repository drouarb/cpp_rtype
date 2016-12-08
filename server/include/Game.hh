#ifndef RTYPE_GAME_HH_
#define RTYPE_GAME_HH_

#include "Level.hh"
#include "Client.hh"
#include <list>

namespace server
{
    class Game
    {
    public:
        Game(int lobbyId);
        Game(int lobbyId, const Level &);
        ~Game();

        void newPlayer(Client *client);
        void removePlayer(Client *client);
        void setLevel(const Level &);
        void tick(round_t);
        int getLobbyId();

    private:
        std::list<Client *> clientList;
        const Level * lvl;
        std::list<IEntity*> entities;
        std::list<IEntity*> destroyedEntities;
        round_t round;
        int gameId;
        entityId_t entityIdCount;


        /**
         * Checks level for new spawns, or whatever the level may tell the game to do.
         */
        void progressLevel();
        /**
         * Must be called after letEntitiesAct and before moveEntities.
         * Checks for future collisions according to the current vector.
         * Changes the vectors so that the entities about to collide touch but do not overlap.
         * Calls the entity's collide() method in case of "collision".
         */
        void checkCollisions();
        /**
         * Here, entities will do their things.
         */
        void letEntitesAct();
        /**
         * Moves the entities according to their vector.
         */
        void moveEntities();
        /**
         * Must be called after moveEntities, and before sending packets.
         */
        void unspawn();
    };
}

#endif