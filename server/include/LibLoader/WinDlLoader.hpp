#pragma once

#include "IDlLoader.hh"
#include "Windows.h"

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
			throw "Failed to load dll";
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
			return (NULL);
		return (static_cast<T *>(creation_fun()));
	}
};