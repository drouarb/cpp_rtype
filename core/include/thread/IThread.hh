//
// Created by greg on 11/12/2016.
//

#ifndef THREADTEST_ITHREAD_HH
#define THREADTEST_ITHREAD_HH

class IThread {
public:
    virtual bool joinable()= 0;

    virtual void join()= 0;

    virtual void detach()= 0;
};

#endif //THREADTEST_ITHREAD_HH
