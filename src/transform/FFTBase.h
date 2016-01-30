#ifndef _FFT_BASE_H
#define _FFT_BASE_H

#include "TransformTypes.h"

namespace Capture
{
	class FFTBase
	{
	protected:
		int N;
	public:
		FFTBase(int length)
			:N(length)
		{}
	
		virtual ~FFTBase()
		{}

		virtual SpectrumType FFT(SignalType x) = 0;
		virtual SignalType IFFT(SpectrumType spectrum) = 0;
	};
}

#endif
