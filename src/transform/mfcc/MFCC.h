#ifndef _MFCC_H
#define _MFCC_H

#include <vector>
#include "../FFTFactory.h"
#include "../TransformTypes.h"

namespace Capture
{
	class MFCC
	{
	private:
		int m_inputSize;
		std::auto_ptr<FFTBase> m_fft;

	public:
		MFCC(int inputSize)
			:m_inputSize(inputSize), m_fft(GetFFT(m_inputSize))
		{}

		std::vector<double> Calculate(const SignalType& source, double sampleRate, int numFeatures=12);
	};
}

#endif
