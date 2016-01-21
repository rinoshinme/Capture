#include "transform.h"
#include <math.h>

#define PI 3.1415926

namespace Capture
{
	// size is assumed to be integer power of 2, not required for simple dft calculation
	void DFT(std::complex<double>* input, std::complex<double>* output, int size, int direction)
	{
		double theta = direction * 2 * PI / size;
		std::complex<double> w(cos(theta), sin(theta));
		for (int j = 0; j < size; ++j)
		{
			output[j] = 0;
			for (int i = 0; i < size; ++i)
			{
				output[j] += input[i] * pow(w, (i * j));
			}
		}
	}
}

