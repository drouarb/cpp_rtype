#include <Core.hh>
#include <iostream>

int main() {
    server::Core *core = nullptr;
    try {
        core = new server::Core("./levels/", 9000);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    core->run();
}