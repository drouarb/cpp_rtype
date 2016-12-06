#pragma once

#include "Windows.h"
#include "IDlLoader.hh"

template <typename T>
class UnixDlLoader : public IDlLoader<T>
{
public:
	UnixDlLoader(LPCTSTR)
	{ }

	~UnixDlLoader()
	{ }

	T * getInstance()
	{
		return (nullptr);
	}
};