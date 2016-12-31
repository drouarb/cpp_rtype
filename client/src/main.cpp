/*
** trouve_b
*/

#include <thread>
#include <sstream>
#include <iostream>
#include "GameClient.hh"
#include "Menu.hh"
#include "Information.hh"
using  namespace client;

int main(int argc, char **argv)
{
    client::GameClient game;
    game.run();
    return (0);
}
