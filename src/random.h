#ifndef _RANDOM_H
#define _RANDOM_H

#include <stdlib.h>
#include <limits.h>

namespace Capture
{
	// generate random number from [0, 1)
	double RandomDouble()
	{
		long x = rand();
		return x * 1.0 / RAND_MAX;
	}


}


#endif

