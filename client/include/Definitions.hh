/*
** trouve_b
*/

#ifndef DEFINITION_CLIENT_HH_
# define DEFINITION_CLIENT_HH_

#include <tuple>

namespace client
{
  enum	Team
    {
      PLAYER,
      ENEMY
    };

  enum	worldEventType
    {
      SPAWN,
      UPDATE,
      MOVE,
      DELETE
    };
}

typedef pos_t		std::pair<uint16_t, uint16_t>;
typedef vec_t		std::pair<uint16_t, uint16_t>;
typedef tick		uint32_t;
typedef id_t		uint16_t;
typedef idtype_t	uint16_t;
typedef UIevent_t	uint16_t;

#endif
