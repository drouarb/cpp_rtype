#ifndef RTYPE_GAME_HH_
#define RTYPE_GAME_HH_

#include "Level.hh"
#include "Client.hh"
#include "network/PacketFactory.hh"
#include "events/Timeline.hh"
#include <list>

#define ROUNDS_BETWEEN_SYN 30

namespace server
{
    class Game
    {
    public:
        Game(network::PacketFactory & packetf, int lobbyId);
        Game(network::PacketFactory & packetf, int lobbyId, const Level &);
        ~Game();

        bool operator==(const Game & other);

        void newPlayer(Client *client);
        void removePlayer(Client *client);
        void setLevel(const Level &);
        void tick();
        gameId_t getLobbyId();
        bool hasClient(const Client &);
        bool empty();
        uint16_t getClientSize();
        round_t getTick();

    private:
        network::PacketFactory & packetf;
        std::list<Client *> clientList;
        const Level * lvl;
        std::vector<Entity*> entities;
        std::vector<Entity*> destroyedEntities;
        round_t round;
        gameId_t gameId;
        entityId_t entityIdCount;
        std::vector<server::event::AGameEvent *> gameEvents;
        round_t lastSyn;
        bool going;


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
        
        pos_t fx(size_t);
        pos_t fxp(size_t);
        pos_t fy(size_t);
        pos_t fyp(size_t);

        /**
         * \defgroup Simulations functions
         * \brief These functions are a way to signal that a certain aspect of the entity has changed.
         * This change needs to be sent to the simulation, and eventually to the client.
         * Several changes may happen for a single entity in a single round. In this case, the last signaled change overwrites the other ones.
         * @{
         */

        void sim_spawn(Entity *entity);
        void sim_move(Entity *entity); //vectors
        void sim_update(Entity *entity); //hp
        void sim_destroy(Entity *entity);

        /**@}*/

        void sendData();
        void sendPacketSync(const Client * client);
        void greetNewPlayer(const Client &);
        void sendSimToNewNotFirst(const Client & client);
        void sendAllMoves();
        void sendSound(const std::string & soundfile);

        bool isFinished();
        void endGame();
    };
}

#endif