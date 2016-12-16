//
// Created by greg on 16/12/2016.
//

#ifndef CPP_RTYPE_MUTEXER_HH
#define CPP_RTYPE_MUTEXER_HH


#include "IMutex.hh"

class Mutexer {
private:
    IMutex *mutex;
public:
    Mutexer(IMutex *);

    virtual ~Mutexer();
};


#endif //CPP_RTYPE_MUTEXER_HH
