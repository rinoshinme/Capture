#include "FirFilter.h"

namespace Capture
{
	FirFilter::FirFilter(double* coef, int sz)
	{
		int p = Power2(sz);
		size = (1 << p);
		a = new double[size];
		buffer = new double[size];

		for (int i = 0; i < size; ++i)
		{
			buffer[i] = 0.0;
			if (i < sz)
				a[i] = coef[i];
			else
				a[i] = 0.0;
		}
		pos = 0;
	}

	FirFilter::FirFilter(const FirFilter& copy)
	{
		size = copy.size;
		pos = copy.pos;
		a = new double[size];
		buffer = new double[size];
		memcpy(a, copy.a, sizeof(double) * size);
		memcpy(buffer, copy.buffer, sizeof(double) * size);
	}

	FirFilter& FirFilter::operator=(const FirFilter& rhs)
	{
		if (this == &rhs)
			return *this;
		size = rhs.size;
		pos = rhs.pos;

		delete[] a;
		a = new double[size];
		memcpy(a, rhs.a, sizeof(double) * size);
		delete[] buffer;
		buffer = new double[size];
		memcpy(buffer, rhs.buffer, sizeof(double) * size);
		return *this;
	}

	double FirFilter::DoProcess(double input)
	{
		buffer[pos] = input;
		double v = 0;
		for (int i = 0; i < size; ++i)
			v += a[i] * buffer[(pos + i) % size];
		pos++;
		if (pos == size)
			pos = 0;
		return v;
	}
}
