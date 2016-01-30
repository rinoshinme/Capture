#include "MelFilter.h"
#include <cmath>

namespace Capture
{
	double LinearToMel(double linearFrequency)
	{
		return 1127.01048 * std::log(1.0 + linearFrequency / 700.0);
	}

	double MelToLinear(double melFrequency)
	{

		return 700.0 * (std::exp(melFrequency / 1127.01048) - 1.0);
	}

	MelFilter::MelFilter(const MelFilter& copy)
		:m_sampleRate(copy.m_sampleRate)
	{
		m_spectrum = std::vector<double>(copy.m_spectrum.size());
		for (int i = 0; i < m_spectrum.size(); ++i)
			m_spectrum[i] = copy.m_spectrum[i];
	}

	MelFilter& MelFilter::operator=(const MelFilter& rhs)
	{
		if (this == &rhs)
			return *this;
		m_sampleRate = rhs.m_sampleRate;
		m_spectrum.resize(rhs.m_spectrum.size());
		for (int i = 0; i < m_spectrum.size(); ++i)
			m_spectrum[i] = rhs.m_spectrum[i];

		return *this;
	}

	void MelFilter::CreateFilter(int filterIndex, double melFilterWidth, int N)
	{
		double melMinFreq = filterIndex * melFilterWidth / 2.0;
		double melCenterFreq = melMinFreq + melFilterWidth / 2.0;
		double melMaxFreq = melMinFreq + melFilterWidth;

		double minFreq = MelToLinear(melMinFreq);
		double centerFreq = MelToLinear(melCenterFreq);
		double maxFreq = MelToLinear(melMaxFreq);

		GenerateFilterSpectrum(minFreq, centerFreq, maxFreq, N);
	}

	double MelFilter::Apply(const SpectrumType& dataSpectrum)
	{
		double value = 0.0;
		int N = dataSpectrum.size();
		for (int i = 0; i < N; ++i)
			value += std::abs(dataSpectrum[i]) * m_spectrum[i];

		return value;
	}


	void MelFilter::GenerateFilterSpectrum(double minFreq, double centerFreq, double maxFreq, int N)
	{
		m_spectrum.clear();
		m_spectrum.resize(N, 0.0);

		int minPos = static_cast<int>(N * minFreq / m_sampleRate);
		int maxPos = static_cast<int>(N * maxFreq / m_sampleRate);
		maxPos = std::min(maxPos, N - 1);
		if (maxPos <= minPos)
			return;

		const double max = 1.0;
		for (int k = minPos; k <= maxPos; ++k)
		{
			double currentFreq = k * 1.0 * m_sampleRate / N;
			if (currentFreq < minFreq)
				m_spectrum[k] = 0.0;
			else if (currentFreq < centerFreq)
				m_spectrum[k] = (currentFreq - minFreq) * max / (centerFreq - minFreq);
			else if (currentFreq < maxFreq)
				m_spectrum[k] = (maxFreq - currentFreq) * max / (maxFreq - centerFreq);
		}
	}
}
