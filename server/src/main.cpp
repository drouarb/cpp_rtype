#include <Core.hh>

int main() {
    server::Core core("./levels/", 9000);

    core.run();
}