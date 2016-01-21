#ifndef _IIR_FILTER_H
#define _IIR_FILTER_H

#include "../utils/helper.h"

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
		IirFilter(double* coef_a, double* coef_b, int sz_a, int sz_b)
		{
			/*
			 * In coef_b, the first 0 term is not included.
			 */
			int pa = Power2(sz_a);
			int pb = Power2(sz_b);
			size_a = (1 << pa);
			size_b = (1 << pb);
			a = new double[size_a];
			b = new double[size_b];
			buffer_a = new double[size_a];
			buffer_b = new double[size_b];

			for (int i = 0; i < size_a; ++i)
			{
				buffer_a[i] = 0.0;
				if (i < sz_a)
					a[i] = coef_a[i];
				else
					a[i] = 0.0;
			}

			for (int i = 0; i < size_b; ++i)
			{
				buffer_b[i] = 0.0;
				if (i < sz_b)
					b[i] = coef_b[i];
				else
					b[i] = 0.0;
			}

			pos_a = 0;
			pos_b = 0;
		}

		IirFilter(const IirFilter& copy)
		{
			size_a = copy.size_a;
			size_b = copy.size_b;
			pos_a = copy.pos_a;
			pos_b = copy.pos_b;
			a = new double[size_a];
			b = new double[size_b];
			buffer_a = new double[size_a];
			buffer_b = new double[size_b];
			memcpy(a, copy.a, sizeof(double) * size_a);
			memcpy(b, copy.b, sizeof(double) * size_b);
			memcpy(buffer_a, copy.buffer_a, sizeof(double) * size_a);
			memcpy(buffer_b, copy.buffer_b, sizeof(double) * size_b);
		}

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

		IirFilter& operator=(const IirFilter& rhs)
		{
			if (this == &rhs)
				return *this;
			size_a = rhs.size_a;
			size_b = rhs.size_b;
			pos_a = rhs.pos_a;
			pos_b = rhs.pos_b;
			delete[] a;
			a = new double[size_a];
			memcpy(a, rhs.a, sizeof(double) * size_a);
			delete[] b;
			b = new double[size_b];
			memcpy(b, rhs.b, sizeof(double) * size_b);
			delete[] buffer_a;
			buffer_a = new double[size_a];
			memcpy(buffer_a, rhs.buffer_a, sizeof(double) * size_a);
			delete[] buffer_b;
			buffer_b = new double[size_b];
			memcpy(buffer_b, rhs.buffer_b, sizeof(double) * size_b);
		}

		double DoProcess(double input)
		{
			buffer_a[pos_a] = input;
			double v = 0;
			for (int i = 0; i < size_a; ++i)
				v += a[i] * buffer_a[(pos_a + i) % size_a];
			for (int i = 0; i < size_b; ++i)
				v += b[i] * buffer_b[(pos_b + i) % size_b];
			buffer_b[pos_b] = v;
			pos_a = (pos_a + 1)%size_a;
			pos_b = (pos_b + 1)%size_b;
			return v;
		}

	};
}



#endif

