//
// Created by greg on 11/12/2016.
//

#ifndef THREADTEST_MUTEX_HH
#define THREADTEST_MUTEX_HH


#include <mutex>
#include "IMutex.hh"

class Mutex : public IMutex {
private:
    std::mutex *m;

    Mutex(const Mutex &);
public:
    Mutex();

    void lock() override;

    bool tryLock() override;

    void unlock() override;

};


#endif //THREADTEST_MUTEX_HH
