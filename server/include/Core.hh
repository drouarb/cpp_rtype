#ifndef RTYPE_SERVER_CORE_HH_
#define RTYPE_SERVER_CORE_HH_

#include <string>
#include <Level.hh>

namespace server {

    class Core {
    private:
        std::vector<Level> levels;
    public:
        /**
         *
         * @param path to a folder
         */
        Core(const std::string &path);

    private:
        void run();
    };

}

#endif