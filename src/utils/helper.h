#ifndef _HELPER_H
#define _HELPER_H

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
}


#endif

