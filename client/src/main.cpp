/*
** trouve_b
*/

#include <thread>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include "GameClient.hh"
#include "Menu.hh"

using  namespace client;

int main(int argc, char **argv)
{
  /*<<<<<<< 47fd50508c59bda1a7ddd96b90ef7068cbda6066
  GameClient toto;
 toto.gameLoop();

 //   AMenu lolo("config/menuTest.json");
 =======*/
  std::string	IP;
  unsigned short		port;

  if (argc < 3)
    {
        std::cerr << "usage : ./rtype_client IP port" << std::endl;
      return (1);
    }
  IP = argv[1];
  std::istringstream strm(argv[2]); strm >> port;
  client::GameClient game;
  game.createNetworkManager();
  game.gameLoop();
  return (0);
    
  //>>>>>>> prepare client for soutenance
  //>>>>>>> prepare client for soutenance
    /*
  unsigned long item;
  
  item = toto.getUi()->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->addItem(UI::ITEM,
									       "/home/celeriy/Downloads/accueil2-hotel-3-etoiles-paris-1.jpg",
                                                                                 250, 250);
    
    toto.getUi()->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->getItem(item)->setImage(
            "/home/celeriy/Downloads/accueil2-hotel-3-etoiles-paris-1.jpg");
    
    toto.getUi()->getWindow(UI::MAIN_WINDOW)->getLayer(UI::GAME)->getItem(item)->setPosition(250, 250);
    
    int i = 0;
    */
}
