//
// Created by drouar_b on 10/25/16.
//

#ifndef CPP_BABEL_INETWORKUTIL_HH
#define CPP_BABEL_INETWORKUTIL_HH

#include <cstdint>
#include <vector>

#define GET_NETSTR(vec, x)    (*static_cast<utils::NetworkString *>(vec[x]))
#define SET_NETSTR(vec, x, y) static_cast<utils::NetworkString *>(vec[x])->assign(y)

#define GET_NETINT(vec, x)    static_cast<utils::NetworkInteger *>(vec[x])->getValue()
#define SET_NETINT(vec, x, y) static_cast<utils::NetworkInteger *>(vec[x])->setValue(y)

#define GET_NETVEC(vec, x)    (*static_cast<utils::NetworkVector *>(vec[x]))

typedef std::vector<uint8_t> t_rawdata;

namespace network {
    namespace utils {
        class INetworkUtil {
        public:
            virtual ~INetworkUtil() { }

            virtual INetworkUtil *clone() = 0;
            virtual uint16_t getSize() const = 0;
            virtual void serialize(t_rawdata *data) const = 0;
            virtual t_rawdata::iterator deserialize(t_rawdata *data) = 0;
            virtual t_rawdata::iterator deserialize(t_rawdata *data, t_rawdata::iterator it) = 0;
        };
    }
}

#endif //CPP_BABEL_INETWORKUTIL_HH
