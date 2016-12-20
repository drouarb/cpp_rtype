//
// Created by drouar_b on 12/19/16.
//

#include "helpers/IStopwatch.hh"

#ifdef _WIN32
#include "helpers/WindowsStopwatch.hh"
#else

#include "helpers/UnixStopwatch.hh"

#endif

helpers::IStopwatch *helpers::IStopwatch::getInstance() {
#ifdef _WIN32
    return (new WindowsStopwatch());
#else
    return (new UnixStopwatch());
#endif
}