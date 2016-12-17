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
  managerUi.getEventObserver()->getEvent(); //TODO à modifier
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

void GameUIInterface::addListEntity(std::vector<Entity *> listentity) {
  for (int i = 0; listentity[i] ; i++)
  {
   auto item =  window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listentity[i]->getTypeid()], listentity[i]->getPos().first, listentity[i]->getPos().second);
    gameItem[listentity[i]->getId()] = item;
  }
}

void GameUIInterface::addEntity(Entity *listEntity) {
  auto item =  window->getLayer(UI::GAME)->addItem(UI::ITEM, typeEntity[listEntity->getTypeid()], listEntity->getPos().first, listEntity->getPos().second);
  gameItem[listEntity->getId()] = item;
}

void GameUIInterface::updateListEntity(std::vector<Entity *> listentity) {
  for (int i = 0; listentity[i] ; i++)
  {
    gameItem[listentity[i]->getId()]->setPosition(listentity[i]->getPos().first, listentity[i]->getPos().second);
  }
}

void GameUIInterface::updateEntity(Entity *entity) {
  gameItem[entity->getId()]->setPosition(entity->getPos().first, entity->getPos().second);
}

void GameUIInterface::deleteListEntity(std::vector<Entity *> listentity) {
  for (int i = 0; listentity[i] ; i++)
  {
    //TODO à rajouter delete item UI
    gameItem.erase(listentity[i]->getId());
  }
}

void GameUIInterface::deleteEntity(Entity *entity) {
        //TODO à rajouter delete item UI
        gameItem.erase(entity->getId());
}
