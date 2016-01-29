#include "OouraFFT.h"

namespace Capture
{
	SpectrumType OouraFFT::FFT(SignalType x)
	{
		double* a = new double[2 * N];
		for (int i = 0; i < N; ++i)
		{
			a[2 * i] = x[i];
			a[2 * i + 1] = 0.0;
		}
		cdft(2*N, -1, a, ip, w);
		SpectrumType spectrum;
		spectrum.resize(N);
		for (int i = 0; i < N; ++i)
			spectrum[i] = Complex(a[2*i], a[2*i+1]);
		delete[] a;

		return spectrum;
	}

	SignalType OouraFFT::IFFT(SpectrumType spectrum)
	{
		double* a = new double[2 * N];
		for (int i = 0; i < N; ++i)
		{
			a[2 * i] = spectrum[i].real();
			a[2 * i + 1] = spectrum[i].imag();
		}

		cdft(2*N, 1, a, ip, w);
		
		double* x = new double[N];
		for (int i = 0; i < N; ++i)
			x[i] = a[2 * i] / static_cast<double>(N);
		SignalType signal(x, x+N);
		delete[] a;
		delete[] x;

		return signal;
	}
}
