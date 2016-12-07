//
// Created by lewis_e on 06/12/16.
//

#ifndef CPP_RTYPE_DEFINITIONS_HH
#define CPP_RTYPE_DEFINITIONS_HH

#include "cstdint"

namespace server {
    typedef uint32_t round_t;
    typedef float pos_t;
    typedef float speed_t;
    typedef int32_t damage_t;
}


#ifdef LOG_ERROR
#define ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr)
#define INFO(expr)
#elif LOG_WARN
#define ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr) std::cerr << expr << std::endl;
#define INFO(expr)
#elif LOG_INFO
#define ERROR(expr) std::cerr << expr << std::endl;
#define WARN(expr) std::cerr << expr << std::endl;
#define INFO(expr) std::cerr << expr << std::endl;
#warning Compilation with LOG_INFO enabled, this may reduce application speed
#else
#define ERROR(expr)
#define WARN(expr)
#define INFO(expr)
#endif

#endif //CPP_RTYPE_DEFINITIONS_HH
