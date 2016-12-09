#ifndef RTYPE_SERVER_CORE_HH_
#define RTYPE_SERVER_CORE_HH_

#include <string>
#include <Level.hh>
#include "NetworkManager.hh"

namespace server {

    class NetworkManager;

    class Core {
    private:
        std::vector<Level> levels;
        NetworkManager *networkManager;
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