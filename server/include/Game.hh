#ifndef RTYPE_GAME_HH_
#define RTYPE_GAME_HH_

#include "Level.hh"
#include "Client.hh"
#include "network/PacketFactory.hh"
#include "events/Timeline.hh"
#include "Grid.hh"
#include <map>
#include <stack>

#define Y_BORDER_WIDTH 10

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
        Grid grid;
        const std::pair<std::string, std::string> * currentGamedata;

        static const std::string playerPaths[4];

        std::vector<Entity*>::iterator vect_erase(std::vector<Entity*>::iterator it, std::vector<Entity*> & vect);

        void progressLevel();
        void checkCollisions();
        void checkCollision(Entity * entity1, Entity * entity2);
        void letEntitesAct();
        void moveEntities();
        void unspawn();
        void manageNewGamedata();

        void checkCollisionsCell(Entity * entity, int cell_x, int cell_y);
        bool willChangeCell(const Entity * entity);
        void spawnEntity(Entity * entity);
        
        pos_t fx(const Entity *) const;
        pos_t fxp(const Entity *) const;
        pos_t fy(const Entity *) const;
        pos_t fyp(const Entity *) const;

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