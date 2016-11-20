//
// Created by drouar_b on 10/25/16.
//

#ifndef CPP_BABEL_NETWORKSTRING_HH
#define CPP_BABEL_NETWORKSTRING_HH

#include <string>
#include "INetworkUtil.hh"

namespace network {
    namespace utils {
        class NetworkString : public std::string, public INetworkUtil {
        public:
            using std::string::string;
            virtual ~NetworkString();

            virtual INetworkUtil *clone();
            virtual uint16_t getSize() const;
            virtual void serialize(t_rawdata *data) const;
            virtual t_rawdata::iterator deserialize(t_rawdata *data);
            virtual t_rawdata::iterator deserialize(t_rawdata *data, t_rawdata::iterator it);
        };
    }
}

#endif //CPP_BABEL_NETWORKSTRING_HH
