#ifndef _DFT_H
#define _DFT_H

#include "FFTBase.h"
#include "TransformTypes.h"

namespace Capture
{
	// calculate DFT using the formula as it is
	class DFT: public FFTBase
	{
	public:
		DFT(int length)
			:FFTBase(length)
		{}

		~DFT()
		{}

		SpectrumType FFT(SignalType input);

		SignalType IFFT(SpectrumType spectrum);
	};
}

#endif
