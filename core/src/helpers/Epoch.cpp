//
// Created by greg on 30/12/16.
//

#include <bits/time.h>
#include <sys/time.h>
#include "helpers/Epoch.hh"

using namespace helpers;

#ifdef WIN32

#else
uint64_t Epoch::getTimeMs() {
    struct timeval tv;

    gettimeofday(&tv, nullptr);

    unsigned long long millisecondsSinceEpoch =
            (unsigned long long)(tv.tv_sec) * 1000 +
            (unsigned long long)(tv.tv_usec) / 1000;
    return millisecondsSinceEpoch;
}

uint64_t Epoch::getTimeS() {
    struct timeval tv;

    gettimeofday(&tv, nullptr);

    unsigned long long second =
            (unsigned long long)(tv.tv_sec) * 1000;
    return second;
}

#endif