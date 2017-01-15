#include <Core.hh>
#include <iostream>

int main(int ac, char **av) {

    int port = 9000;

    if (ac == 2)
        port = atoi(av[1]);

    server::Core *core = nullptr;
    try {
        core = new server::Core(std::string("levels"), port);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    core->run();
    return (0);
}