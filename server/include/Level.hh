#ifndef RTYPE_LEVEL_HH_
#define RTYPE_LEVEL_HH_

#include "Spawn.hh"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <ostream>

namespace server {
    class Level {
    public:
        /**
        * Read JSON from a the given file and translate it to a level.
        * @note Clears existing contents of property tree.  In case of error the
        *       property tree unmodified.
        * @throw json_parser_error In case of error deserializing the property
        *                          tree.
        * @param filename Name of file from which to read in the property tree.
        */
        Level(const std::string &filepath);

        ~Level();

        /**
         * @param tick
         * @return
         */
        const std::vector<Spawn> *getNewSpawns(round_t tick) const;
        bool isOver(round_t tick) const;

    private:
        std::map<round_t, std::vector<Spawn>> spawns;
        std::string name;
        round_t end;
    };
}

#endif