/*
** trouve_b
*/

#include "GameUIInterface.hh"

using namespace client;

GameUIInterface::GameUIInterface()
{
}

GameUIInterface::~GameUIInterface()
{
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

typeide_t	GameUIInterface::getNextId()
{
  static typeide_t	id = 0;
  return (id++);
}
