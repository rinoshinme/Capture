#ifndef _DFT_H
#define _DFT_H

#include "TransformTypes.h"

namespace Capture
{
	// calculate DFT using the formula as it is
	class DFT
	{
	private:
		int N;

	public:
		DFT(int length)
			:N(length)
		{}

		~DFT()
		{}

		SpectrumType FFT(SignalType input);

		SignalType IFFT(SpectrumType spectrum);
	};
}

#endif
