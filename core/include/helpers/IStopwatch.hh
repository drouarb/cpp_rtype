//
// Created by drouar_b on 12/19/16.
//

#ifndef CPP_RTYPE_ISTOPWATCH_HH
#define CPP_RTYPE_ISTOPWATCH_HH

namespace helpers {
    class IStopwatch {
    public:
        virtual ~IStopwatch() { }
        virtual void set() = 0;
        virtual long elapsedMs() = 0;

        static IStopwatch *getInstance();
    };
}

#endif //CPP_RTYPE_ISTOPWATCH_HH
