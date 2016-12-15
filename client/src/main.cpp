#include <thread>
#include <unistd.h>
#include "GameClient.hh"
using  namespace client;
int main() {
    GameClient toto;
    unsigned long item;
    item = toto.getUi()->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->addItem(UI::ITEM,
                                                                                 "/home/celeriy/Downloads/accueil2-hotel-3-etoiles-paris-1.jpg",
                                                                                 250, 250);
    toto.getUi()->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->getItem(item)->setImage(
            "/home/celeriy/Downloads/accueil2-hotel-3-etoiles-paris-1.jpg");
    toto.getUi()->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->getItem(item)->setPosition(250, 250);
    int i = 0;
    toto.gameLoop();
}