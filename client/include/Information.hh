//
// Created by celeriy on 22/12/16.
//

#ifndef CPP_RTYPE_INFORMATION_HH_HH
#define CPP_RTYPE_INFORMATION_HH_HH

#include <string>
#include <sstream>
#include <iostream>

namespace client {
    enum information : int {
        I_DEFAULT = 0,
        I_JOIN = 1,
        I_REGISTER = 2,
        I_DISCONNECT = 3,
        I_QUIT = 4,
        I_ASKLEADERBOARD = 5,
        I_ASKLIST = 6,
        I_PLAYER_MOVE = 7,
        I_CONNECTION = 8
    };
    struct  s_info
    {
        client::information info;
    };
    struct s_connection : s_info
    {
        unsigned short	 port;
        std::string ip;
    };

    struct s_register : s_info
    {
        std::string name;
    };

    struct s_join : s_info
    {
       uint8_t roomid;
    };
    static s_info* parse(information type , const std::string & value)
    {
        if (type == I_CONNECTION)
        {
            struct  s_connection* res = new s_connection;
            res->info = type;
            res->ip = value.substr(0, value.find(":"));
            std::istringstream strm(value.substr(value.find(":") + 1, value.size()));
            strm >> res->port;
            return res;
        }
        else if( type == I_REGISTER)
        {
            s_register *reg = new s_register;
            reg->name = value;
            reg->info = type;
            return reg;
        }
        else if (type == I_JOIN)
        {
                struct  s_join* res = new s_join;
                res->info = type;
                std::istringstream strm(value.substr(value.find(":") + 1, value.size()));
                strm >> res->roomid;
            std::cout << res->roomid << std::endl;
                return res;
        }
        return nullptr;
    }
}


#endif //CPP_RTYPE_INFORMATION_HH_HH
