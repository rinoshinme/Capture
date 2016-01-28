#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdlib.h>
#include <limits.h>

namespace Capture
{
	// find lowest n s.t. 2**n >= value
	long Power2(long value)
	{
		long p = 0;
		long v = 1;
		while (v < value)
		{
			v *= 2;
			p++;
		}
		return p;
	}

	// generate random number from [0, 1)
	inline double RandomDouble()
	{
		return std::rand() / static_cast<double>(RAND_MAX);
	}
}

#endif
