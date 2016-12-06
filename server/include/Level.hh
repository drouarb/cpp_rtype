#ifndef RTYPE_LEVEL_HH_
#define RTYPE_LEVEL_HH_

#include "Spawn.hh"
#include <string>
#include <vector>
#include <list>

namespace server
{
    class Level
    {
    public:
        Level(const std::string & filepath);
        ~Level();

        std::list<Spawn*> * getNewSpawns();

    private:
        std::vector<Spawn> spawns;
    };
}

#endif