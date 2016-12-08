#pragma once


#define DLL_FUN_NAME "create_entity"
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

