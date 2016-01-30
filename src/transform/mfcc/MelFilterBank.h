#ifndef _MEL_FILTER_BANK_H
#define _MEL_FILTER_BANK_H

#include <vector>
#include "MelFilter.h"

namespace Capture
{
	class MelFilterBank
	{
	private:
		std::vector<MelFilter> m_filters;
		double m_sampleRate;
		int N;

	public:
		MelFilterBank(double sampleRate, int length,
			double melFilterWidth = 200.0,
			int bankSize = 24);

		std::vector<double> ApplyAll(const SpectrumType& frameSpectrum);

		int GetSpectrumLength() const
		{
			return N;
		}

		int Size() const
		{
			return m_filters.size();
		}

		int GetSampleRate() const
		{
			return m_sampleRate;
		}
	};
}

#endif
