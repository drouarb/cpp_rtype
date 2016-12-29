#ifndef RTYPE_SPAWN_HH_
#define RTYPE_SPAWN_HH_

#include "Definitions.hh"
#include "Entity.hh"

namespace server
{
    struct Spawn
    {
        Spawn();
        Spawn(const Spawn &);
        ~Spawn();

        Spawn & operator=(const Spawn &);

        std::string dlName;
        round_t time;
        pos_t posX;
        pos_t posY;

        Entity *trigger(entityId_t id, round_t round, const std::vector<Entity *> &entities);
    };
}

#endif