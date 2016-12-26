//
// Created by lewis_e on 06/12/16.
//

#ifndef CPP_RTYPE_DEFINITIONS_HH
#define CPP_RTYPE_DEFINITIONS_HH

#include "cstdint"

#define ROUND_DURATION_MS 30
#define MAX_PLAYERS 4

namespace server {

    enum Team : unsigned int
    {
        NEUTRAL = 0,    //! not applicable (non-actor entities)
        PLAYER  = 1,    //! players' team
        FOE     = 2     //! default team for enemies
        //! Other values greater than 2 may be used in the dynamic libraries. The server is not concerned by them.
    };

    enum Tribool : int8_t
    {
        FALSE   = false,
        TRUE    = true,
        NA      = -1
    };

    typedef uint32_t round_t;
    typedef float pos_t;
    typedef float speed_t;
    typedef int16_t hp_t;
    typedef uint8_t attackId_t;
    typedef unsigned long clientId_t;
    typedef int gameId_t;
    typedef uint32_t entityId_t;
    typedef uint32_t eventId_t;
}

#define FIELD_WIDTH 800
#define FIELD_HEIGHT 600
#define FIELD_BORDER_LEFT 0
#define FIELD_BORDER_RIGHT (FIELD_BORDER_LEFT + FIELD_WIDTH)
#define LEFT_MARGIN 100
#define RIGHT_MARGIN (LEFT_MARGIN)

#ifdef LOG_INFO
#define ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr) std::cout << "---- WARN ----- " << expr << std::endl;
#define INFO(expr) std::cout << "---- INFO ----- " << expr << std::endl;
#elif LOG_ERROR
#define ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr)
#define INFO(expr)
#elif LOG_WARN
#define ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr) std::cerr << expr << std::endl;
#define INFO(expr)
#else
#define ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr)
#define INFO(expr)
#endif

#endif //CPP_RTYPE_DEFINITIONS_HH
