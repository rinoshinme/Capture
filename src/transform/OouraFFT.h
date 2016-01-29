#ifndef _OOURA_FFT_H
#define _OOURA_FFT_H

#include "transform_types.h"
#include <math.h>

extern "C" {
    void cdft(int, int, double *, int *, double *);
    // void rdft(int, int, double *, int *, double *);
}

namespace Capture
{
	class OouraFFT
	{
	private:
		int N;
		int* ip;
		double* w;
	public:
		OouraFFT(int length)
			:N(length)
		{
			ip = new int[static_cast<int>(2 + sqrt(static_cast<double>(N)))];
			w = new double[N / 2];
			ip[0] = 0;
		}

		~OouraFFT()
		{
			delete[] ip;
			delete[] w;
		}

		SpectrumType FFT(SignalType x);

		SignalType IFFT(SpectrumType spectrum);
	};
}

#endif
