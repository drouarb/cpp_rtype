#include <Core.hh>
#include <iostream>

int main() {
    server::Core *core = nullptr;
    try {
        core = new server::Core(std::string("levels") + SYSTEM_FOLDER, 9000);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    core->run();
    return (0);
}