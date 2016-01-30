#include "DFT.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

namespace Capture
{
	SpectrumType DFT::FFT(SignalType x)
	{
		SpectrumType spectrum(N);
		Complex j(0, 1);
		Complex WN = std::exp((-j) * 2.0 * M_PI / static_cast<double>(N));

		for (int k = 0; k < N; ++k)
		{
			Complex sum(0, 0);
			for (int n = 0; n < N; ++n)
			{
				sum += x[n] * std::pow(WN, n * k);
			}
			spectrum[k] = sum;
		}
		return spectrum;
	}

	SignalType DFT::IFFT(SpectrumType spectrum)
	{
		SignalType x(N);
		Complex j(0, 1);
		Complex WN = std::exp((-j) * 2.0 * M_PI / static_cast<double>(N));
		for (int k = 0; k < N; ++k)
		{
			Complex sum(0, 0);
			for (int n = 0; n < N; ++n)
				sum += spectrum[n] * std::pow(WN, -static_cast<int>(n * k));
			x[k] = std::abs(sum) / static_cast<double>(N);
		}
		return x;
	}
}
