#include "FFTFactory.h"
#include "OouraFFT.h"
#include "DFT.h"

namespace Capture
{
	std::auto_ptr<FFTBase> GetFFT(int length, FFTType type)
	{
		if (type == OouraFFTType)
			return std::auto_ptr<FFTBase>(new OouraFFT(length));
		else
			return std::auto_ptr<FFTBase>(new DFT(length));
	}
}
