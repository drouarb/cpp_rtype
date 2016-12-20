//
// Created by greg on 11/12/2016.
//

#ifndef THREADTEST_IMUTEX_HH
#define THREADTEST_IMUTEX_HH

class IMutex {
public:
    virtual void lock()= 0;

    virtual bool tryLock()= 0;

    virtual void unlock()= 0;
};

#endif //THREADTEST_IMUTEX_HH
