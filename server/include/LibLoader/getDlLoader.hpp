//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_GETDLLOADER_HPP
#define CPP_RTYPE_GETDLLOADER_HPP

//#include <winnt.h>
#include <string>
#ifdef _WIN32
#include "Windows.h"
#include <tchar.h>
#include "WinDlLoader.hpp"
#define SHARED_LIB_EXTENTION ".dll"
#else
#include "UnixDlLoader.hpp"
#define SHARED_LIB_EXTENTION ".so"
#endif

template <typename T>
IDlLoader<T> * getDlLoader(const std::string &path)
{
    std::string finalPath = std::string(path + SHARED_LIB_EXTENTION);
#ifdef _WIN32
    return (new WinDlLoader<T>(__T(finalPath.c_str())));
#else
    return (new UnixDlLoader<T>(finalPath));
#endif
}



#endif //CPP_RTYPE_GETDLLOADER_HPP
