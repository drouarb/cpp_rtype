#pragma once


#define DLL_FUN_NAME "getInstance"
#ifdef WIN32
#define DLL_EXTENSION ""
#else
#define DLL_EXTENSION ""
#endif



template <typename T>
class IDlLoader
{

public:
	virtual ~IDlLoader() { }

	virtual T * getInstance() = 0;
};

