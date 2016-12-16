/*
** trouve_b
*/

#include "GameUIInterface.hh"

using namespace client;

GameUIInterface::GameUIInterface(IEventHandler *handler)
{
  managerUi.init(1920, 1020);
  managerUi.getEventObserver()->setEventManager(handler);
  managerUi.getEventObserver()->listen(managerUi.getWindow(UI::MAIN_WINDOW));
}

GameUIInterface::~GameUIInterface()
{
}

void		GameUIInterface::initUI()
{
  window = managerUi.getWindow(UI::MAIN_WINDOW);
}

void		GameUIInterface::displaySimple()
{
  window->display();
}

typeide_t	GameUIInterface::registerNewSprite(const std::string &str)
{
  std::map<typeide_t, std::string>::iterator it;

  it = typeEntity.begin();
  while (it != typeEntity.end())
    {
      if (it->second == str)
	return (it->first);
      ++it;
    }
  typeide_t newid = getNextId();
  typeEntity.insert(std::pair<typeide_t, std::string>(newid, str));
  return (newid);
}

void                GameUIInterface::feedLeaderBoard(std::vector<std::pair<uint32_t, std::string> > nleaderBoard)
{
  leaderBoard = nleaderBoard;
}

void                GameUIInterface::feedGameList(std::vector<std::pair<uint8_t, uint16_t> > ngameList)
{
  gameList = ngameList;
}

typeide_t	GameUIInterface::getNextId()
{
  static typeide_t	id = 0;
  return (id++);
}
