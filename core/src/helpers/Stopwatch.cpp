//
// Created by drouar_b on 12/19/16.
//

#include "helpers/IStopwatch.hh"

#ifdef WIN32
#include "helpers/WindowsStopwatch.hh"
#else

#include "helpers/UnixStopwatch.hh"

#endif

helpers::IStopwatch *helpers::IStopwatch::getInstance() {
#ifdef WIN32
    return (new WindowsStopwatch());
#else
    return (new UnixStopwatch());
#endif
}