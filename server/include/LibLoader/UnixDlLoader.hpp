#pragma once

#include <dlfcn.h>
#include <stdexcept>
#include "string"
#include "IDlLoader.hh"

template <typename T>
class UnixDlLoader : public IDlLoader<T>
{
private:
    void *handle;
    typedef T* (*construtor)();

public:
	UnixDlLoader(const std::string &path)
	{
        handle = dlopen(path.c_str(), RTLD_NOW);
        if (handle == nullptr) {
            throw std::runtime_error("Error when loading " + path);
        }
    }

	~UnixDlLoader()
	{
        dlclose(this->handle);
    }

	T * getInstance()
	{
        void *pVoid = dlsym(this->handle, DLL_FUN_NAME);
        if (pVoid == NULL) {
            throw std::runtime_error("Cannot find " + std::string(DLL_FUN_NAME));
        }
        return (reinterpret_cast<T *(*)()>(pVoid))();
	}
};