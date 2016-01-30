#ifndef _FFT_FACTORY_H
#define _FFT_FACTORY_H

#include "FFTBase.h"
#include <memory>

namespace Capture
{
	enum FFTType
	{
		OouraFFTType,
		DFTType,
	};

	// FFT object should always be generated using this factory method
	std::auto_ptr<FFTBase> GetFFT(int length, FFTType type=OouraFFTType);
}

#endif
