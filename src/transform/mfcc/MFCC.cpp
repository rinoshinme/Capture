#include "MFCC.h"
#include "MelFilterBank.h"
#include "../DCT.h"

namespace Capture
{
	std::vector<double> MFCC::Calculate(const SignalType& source, double sampleRate, int numFeatures)
	{
		SpectrumType spectrum = m_fft->FFT(source);
		MelFilterBank bank(sampleRate, m_inputSize);
		std::vector<double> filterOutput = bank.ApplyAll(spectrum);
		DCT dct;
		return dct.ApplyDCT(filterOutput, numFeatures);
	}
}
