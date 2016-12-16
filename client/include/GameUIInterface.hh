/*
** trouve_b
*/

#ifndef GAMEUIINTERFACE_HH_
# define GAMEUIINTERFACE_HH_

#include <string>
#include <map>
#include "Definitions.hh"

namespace client
{
  class GameUIInterface
  {
  private:
    std::map<typeide_t, std::string>	typeEntity;
  public:
    GameUIInterface();
    ~GameUIInterface();
    typeide_t		registerNewSprite(const std::string &);
  private:
    typeide_t		getNextId();
  };
}

#endif /*GAMEUIINTERFACE_HH_*/
