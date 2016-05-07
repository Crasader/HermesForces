#ifndef UTILITY_H
#define UTILITY_H
#include "define.h"

namespace Utility{
	inline long getCurrentTime()
	{
		struct timeval tv;
		gettimeofday(&tv,NULL);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}
#endif