#ifndef _IIR_FILTER_H
#define _IIR_FILTER_H

#include "../source.h"
#include <string.h>

namespace Capture
{
	/* Real-time iir filter */
	class IirFilter
	{
	private:
		int size_a;
		int size_b;
		double* buffer_a;
		double* buffer_b;
		double* a;
		double* b;
		int pos_a;
		int pos_b;

	public:
		/* constructors and destructor */
		IirFilter()
			:size_a(0), size_b(0), pos_a(0), pos_b(0)
		{
			buffer_a = new double[0];
			buffer_b = new double[0];
			a = new double[0];
			b = new double[0];
		}

		IirFilter(double* coef_a, double* coef_b, int sz_a, int sz_b);

		IirFilter(const IirFilter& copy);

		~IirFilter()
		{
			if (a)
				delete[] a;
			if (b)
				delete[] b;
			if (buffer_a)
				delete[] buffer_a;
			if (buffer_b)
				delete[] buffer_b;
		}

		IirFilter& operator=(const IirFilter& rhs);

		// method
		double DoProcess(double input);
	};
}

#endif
