/*
** trouve_b
*/

#ifndef GAMEUIINTERFACE_HH_
# define GAMEUIINTERFACE_HH_

#include <string>
#include <map>
#include "Definitions.hh"
#include "Entity.hh"
#include "IEventHandler.hh"
#include "UI/UIManager.hh"

namespace client
{
  class GameUIInterface
  {
  private:
    std::map<typeide_t, std::string>			typeEntity;
    std::vector<std::pair<uint8_t, uint16_t> >		gameList;
    std::vector<std::pair<uint32_t, std::string> >	leaderBoard;
    UI::UIManager					managerUi;
    UI::IWindow						*window;
  private:
    GameUIInterface() {};
  public:
    GameUIInterface(IEventHandler *);
    ~GameUIInterface();
    void		initUI();
    void		displaySimple();
    typeide_t		registerNewSprite(const std::string &);
    void		feedLeaderBoard(std::vector<std::pair<uint32_t, std::string> > leaderBoard);
    void		feedGameList(std::vector<std::pair<uint8_t, uint16_t> > gameList);
  private:
    typeide_t		getNextId();
  };
}

#endif /*GAMEUIINTERFACE_HH_*/
