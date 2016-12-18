//
// Created by greg on 08/12/2016.
//

#ifndef CPP_RTYPE_CLIENTCONTAINER_HH
#define CPP_RTYPE_CLIENTCONTAINER_HH

#include <map>
#include <list>
#include <Client.hh>

namespace server {

    class ClientContainer : protected std::map<clientId_t , Client> {
        std::list<Client> clientList;

    public:
        Client &get(clientId_t id);

        Client &create(unsigned long id);

        void remove(clientId_t id);

        const std::list<Client> &toStdList() const;
    };

}


#endif //CPP_RTYPE_CLIENTCONTAINER_HH
