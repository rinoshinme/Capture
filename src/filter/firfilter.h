#ifndef _FIR_FILTER
#define _FIR_FILTER

#include "../source.h"
#include <string.h>

namespace Capture
{
	/* Real-time fir filter */
	class FirFilter
	{
	private:
		double* a;
		double* buffer;
		int size;
		int pos;

	public:
		/* constructors and destructor */
		FirFilter()
			:size(0), pos(0), a(NULL), buffer(NULL)
		{}

		FirFilter(double* coef, int sz);

		FirFilter(const FirFilter& copy);

		~FirFilter()
		{
			if (a)
				delete[] a;
			if (buffer)
				delete[] buffer;
		}

		FirFilter& operator=(const FirFilter& rhs);
		
		// methods
		double DoProcess(double input);
	};
}

#endif
