#include "MelFilterBank.h"

namespace Capture
{
	MelFilterBank::MelFilterBank(double sampleRate, int length, double melFilterWidth, int bankSize)
		:m_sampleRate(sampleRate), N(length), m_filters()
	{
		m_filters.reserve(bankSize);
		for (int i = 0; i < bankSize; ++i)
		{
			m_filters.push_back(MelFilter(m_sampleRate));
			m_filters[i].CreateFilter(i, melFilterWidth, N);
		}
	}

	std::vector<double> MelFilterBank::ApplyAll(const SpectrumType& frameSpectrum)
	{
		int size = m_filters.size();
		std::vector<double> output(size, 0.0);
		for (int i = 0; i < size; ++i)
			output[i] = m_filters[i].Apply(frameSpectrum);
		return output;
	}
}
