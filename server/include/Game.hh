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

        bool operator==(const Game & other);

        void newPlayer(Client *client);
        void removePlayer(Client *client);
        void setLevel(const Level &);
        void tick();
        gameId_t getLobbyId();
        bool hasClient(const Client &);
        bool empty();

    private:
        std::list<Client *> clientList;
        const Level * lvl;
        std::vector<Entity*> entities;
        std::vector<Entity*> destroyedEntities;
        round_t round;
        gameId_t gameId;
        entityId_t entityIdCount;

        std::vector<Entity*>::iterator vect_erase(std::vector<Entity*>::iterator it, std::vector<Entity*> & vect);


        /**
         * Checks level for new spawns, or whatever the level may tell the game to do.
         */
        void progressLevel();
        /**
         * Must be called after letEntitiesAct and before moveEntities.
         * Checks for future collisions according to the current vector.
         * Changes the vectors so that the entities about to collide touch but do not overlap.
         * Calls the entity's collide() method in case of collision.
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
        
        pos_t fx(int);
        pos_t fxp(int);
        pos_t fy(int);
        pos_t fyp(int);
        pos_t fx(size_t);
        pos_t fxp(size_t);
        pos_t fy(size_t);
        pos_t fyp(size_t);

        /**
         * These functions are a way to signal that a certain aspect of the entity has changed.
         * This change needs to be sent to the simulation, and eventually to the client.
         * Several changes may happen for a single entity in a single round. In this case, the last signaled change overwrites the other ones.
         */
        void sim_spawn(Entity *);
        void sim_move(Entity *); //vectors
        void sim_update(Entity *); //hp
        void sim_destroy(Entity *);
        /**
         * Sends data for this round to the clients.
         */
        void sendData();
    };
}

#endif