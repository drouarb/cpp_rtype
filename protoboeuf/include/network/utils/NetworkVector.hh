//
// Created by drouar_b on 11/11/16.
//

#ifndef CPP_BABEL_NETWORKVECTOR_HH
#define CPP_BABEL_NETWORKVECTOR_HH

#include "NetworkInteger.hh"
#include "NetworkString.hh"

namespace network {
    namespace utils {
        class NetworkVector: public INetworkUtil {
        public:
            NetworkVector(uint8_t lensize, std::vector<INetworkUtil *> schema);
            ~NetworkVector();

            virtual INetworkUtil *clone();
            virtual uint16_t getSize() const;
            virtual void serialize(t_rawdata *data) const;
            virtual t_rawdata::iterator deserialize(t_rawdata *data);
            virtual t_rawdata::iterator deserialize(t_rawdata *data, t_rawdata::iterator it);

            void resize(size_t size);
            size_t size();
            std::vector<INetworkUtil *> back();
            std::vector<INetworkUtil *> front();
            std::vector<INetworkUtil *> &operator[](size_t idx);

        private:
            t_rawdata::iterator deserializeSchema(t_rawdata *data, t_rawdata::iterator it);

        private:
            const uint8_t lensize;
            const std::vector<INetworkUtil *> schema;
            std::vector<std::vector<INetworkUtil *>> data;
        };
    }
}

#endif //CPP_BABEL_NETWORKVECTOR_HH
