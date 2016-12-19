//
// Created by drouar_b on 12/19/16.
//

#ifndef CPP_RTYPE_UNIXSTOPWATCH_HH
#define CPP_RTYPE_UNIXSTOPWATCH_HH

#include <ctime>
#include <Windows.h>
#include "IStopwatch.hh"

namespace helpers {
    class WindowsStopwatch: public IStopwatch {
    public:
        WindowsStopwatch();
        virtual ~WindowsStopwatch();

        virtual void set();
        virtual long elapsedMs();

    private:
        unsigned long tick;
    };
}

#endif //CPP_RTYPE_UNIXSTOPWATCH_HH
