//
// Created by greg on 08/12/2016.
//

#ifndef CPP_RTYPE_CLIENTCONTAINER_HH
#define CPP_RTYPE_CLIENTCONTAINER_HH

#include <map>
#include <list>
#include <Client.hh>

namespace server {

    class ClientContainer : protected std::map<int, Client> {
        std::list<Client> clientList;

    public:
        Client &get(int id);

        Client &create(int id);

        void remove(int id);

        const std::list<Client> &toStdList() const;
    };

}


#endif //CPP_RTYPE_CLIENTCONTAINER_HH
