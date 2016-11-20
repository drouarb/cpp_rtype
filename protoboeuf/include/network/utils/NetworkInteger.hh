//
// Created by drouar_b on 10/25/16.
//

#ifndef CPP_BABEL_NETWORKINTEGER_HH
#define CPP_BABEL_NETWORKINTEGER_HH

#include <cstdint>
#include <stdio.h>

#ifdef _WIN32

#include <BaseTsd.h>
typedef SSIZE_T ssize_t;

#endif

#include "INetworkUtil.hh"

namespace network {
    namespace utils {
        class NetworkInteger: public INetworkUtil {
        public:
            NetworkInteger(uint8_t size, ssize_t i = 0);
            virtual ~NetworkInteger();

            virtual INetworkUtil *clone();
            virtual uint16_t getSize() const;
            virtual void serialize(t_rawdata *data) const;
            virtual t_rawdata::iterator deserialize(t_rawdata *data);
            virtual t_rawdata::iterator deserialize(t_rawdata *data, t_rawdata::iterator it);

            ssize_t getValue() const;
            void setValue(ssize_t val);

            ssize_t operator=(ssize_t val);
        private:
            ssize_t i;
            uint8_t size;

            static const std::vector<uint64_t> intMask;
        };
    }
}

#endif //CPP_BABEL_NETWORKINTEGER_HH
