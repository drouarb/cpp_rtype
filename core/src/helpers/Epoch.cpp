//
// Created by greg on 30/12/16.
//

#include "helpers/Epoch.hh"

using namespace helpers;

#ifdef WIN32
uint64_t Epoch::getTimeMs() {
 // the system time
    SYSTEMTIME systemTime;
    GetSystemTime( &systemTime );

    // the current file time
    FILETIME fileTime;
    SystemTimeToFileTime( &systemTime, &fileTime );

    // filetime in 100 nanosecond resolution
    ULONGLONG fileTimeNano100;
    fileTimeNano100 = (((ULONGLONG) fileTime.dwHighDateTime) << 32) + fileTime.dwLowDateTime;

    //to milliseconds and unix windows epoche offset removed
    ULONGLONG posixTime = fileTimeNano100/10000 - 11644473600000;
    return posixTime;
}

uint64_t Epoch::getTimeS() {
 // the system time
    SYSTEMTIME systemTime;
    GetSystemTime( &systemTime );

    // the current file time
    FILETIME fileTime;
    SystemTimeToFileTime( &systemTime, &fileTime );

    // filetime in 100 nanosecond resolution
    ULONGLONG fileTimeNano100;
    fileTimeNano100 = (((ULONGLONG) fileTime.dwHighDateTime) << 32) + fileTime.dwLowDateTime;

    //to milliseconds and unix windows epoche offset removed
    ULONGLONG posixTime = fileTimeNano100/10000 - 11644473600000;
    return posixTime / 1000;
}

#else

#include <bits/time.h>
#include <sys/time.h>


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