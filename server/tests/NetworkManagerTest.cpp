//
// Created by greg on 09/12/2016.
//

#include <Core.hh>

class NetworkManagerTest : public server::NetworkManager
{
public:
    NetworkManagerTest(server::Core *core) : NetworkManager(core) {}

    void setCore(server::Core *core) {

    };
};

int     main()
{

    server::Core core("./levels/");

    core.run();

}