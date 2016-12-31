//
// Created by lewis_e on 06/12/16.
//

#ifndef CPP_RTYPE_DEFINITIONS_HH
#define CPP_RTYPE_DEFINITIONS_HH

#include "cstdint"

#define ROUND_DURATION_MS 25
#define MAX_PLAYERS 4

#define NOATTACK ((attackId_t)-1)

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
        T_FALSE   = 0,
        T_TRUE    = 1,
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
    typedef uint32_t score_t;
}

#define FIELD_WIDTH 1920
#define FIELD_HEIGHT 1080
#define FIELD_BORDER_LEFT 0
#define FIELD_BORDER_RIGHT (FIELD_BORDER_LEFT + FIELD_WIDTH)
#define LEFT_MARGIN 0
#define RIGHT_MARGIN 200

#define ROUNDS_BETWEEN_SYN 30


#ifdef LOG_INFO
#define LOG_ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr) std::cout << "---- WARN ----- " << expr << std::endl;
#define INFO(expr) std::cout << "---- INFO ----- " << expr << std::endl;
#elif LOG_ERROR
#define LOG_ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr)
#define INFO(expr)
#elif LOG_WARN
#define LOG_ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr) std::cerr << expr << std::endl;
#define INFO(expr)
#else
#define LOG_ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr)
#define INFO(expr)
#endif

#ifdef WIN32
#define SYSTEM_FOLDER "\\"
#else
#define SYSTEM_FOLDER "/"
#endif

#endif //CPP_RTYPE_DEFINITIONS_HH
