//
// Created by drouar_b on 12/19/16.
//

#ifndef CPP_RTYPE_UNIXSTOPWATCH_HH
#define CPP_RTYPE_UNIXSTOPWATCH_HH

#include <ctime>
#include "IStopwatch.hh"

namespace helpers {
    class UnixStopwatch: public IStopwatch {
    public:
        UnixStopwatch();
        virtual ~UnixStopwatch();

        virtual void set();
        virtual long elapsedMs();

    private:
        struct timeval startTime;
    };
}

#endif //CPP_RTYPE_UNIXSTOPWATCH_HH
