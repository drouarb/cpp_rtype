#pragma once

#include <winnt.h>

#define DLL_FUN_NAME "create_entity"

template <typename T>
class IDlLoader
{
public:
	virtual ~IDlLoader() { }

	virtual T * getInstance() = 0;
};

