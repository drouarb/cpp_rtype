#pragma once

#include "IDlLoader.hh"
#include "Windows.h"
#include <wchar.h>
#include <stdexcept>

template<typename T>
class WinDlLoader : public IDlLoader<T>
{
private:
	typedef T * (*fun_ptr)();
	HMODULE lib_handle;

public:
	WinDlLoader(LPCTSTR dll_name) : lib_handle(NULL)
	{
		lib_handle = LoadLibrary(dll_name);
		if (lib_handle == NULL)
			throw std::runtime_error("Failed to load dll: " + std::string(dll_name) + " : not a library");
	}

	~WinDlLoader()
	{
		if (lib_handle)
			FreeLibrary(lib_handle);
	}
	T * getInstance()
	{
		if (lib_handle == NULL)
			return (NULL);
		fun_ptr creation_fun = (fun_ptr)GetProcAddress(lib_handle, DLL_FUN_NAME);
		if (creation_fun == NULL)
			throw std::runtime_error("Failed to load dll : cannot find entryPoint");
		T *instance = static_cast<T *>(creation_fun());
		if (instance == nullptr) {
			throw std::runtime_error("Failed to load dll: instance was nullptr");
		}
		return (instance);
	}
};