//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_GETDLLOADER_HPP
#define CPP_RTYPE_GETDLLOADER_HPP

//#include <winnt.h>
#include <string>
#ifdef _WIN32
#include <tchar.h>
#endif
#include "Windows.h"
#include "WinDlLoader.hpp"

template <typename T>
IDlLoader<T> * getDlLoader(const std::string &path)
{
#ifdef _WIN32
    return (new WinDlLoader<T>(__T(path.c_str())));
#else
    return (new UnixDlLoader<T>(path));
#endif
}



#endif //CPP_RTYPE_GETDLLOADER_HPP
