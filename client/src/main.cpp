/*
** trouve_b
*/

#include <thread>
#include <sstream>
#include <iostream>
#include "GameClient.hh"
#include "Menu.hh"
#include "Information.hh"

using namespace client;
#ifdef _WIN32
#else

#include <X11/Xlib.h>

#endif

int main(int argc, char **argv) {
#ifdef _WIN32
#else
    XInitThreads();
#endif
    client::GameClient game;
    game.run();
    return (0);
}
