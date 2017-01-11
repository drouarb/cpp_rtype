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
      SPAWN = 0x01,
      UPDATE = 0x02,
      MOVE = 0x03,
      DELETE = 0x04
    };

    struct Event
    {
      Event()
      {key = -42;pressed = false;}
      Event(short nkey, bool npressed)
      {key = nkey; pressed = npressed;}
      short       key;
      bool        pressed;
    };
}

typedef std::pair<int16_t, int16_t>	pos_t;
typedef std::pair<int16_t, int16_t>	vec_t;
typedef uint32_t			tick;
typedef uint32_t			ide_t;
typedef uint16_t			typeide_t;
typedef int16_t				UIevent_t;

#endif
