#ifndef _MEL_FILTER_H
#define _MEL_FILTER_H

#include "../TransformTypes.h"
#include <vector>

namespace Capture
{
	double LinearToMel(double linearFrequency);

	double MelToLinear(double melFrequency);

	// a melfilter is a triangle
	class MelFilter
	{
	private:
		double m_sampleRate;
		std::vector<double> m_spectrum;

	public:
		MelFilter(double sampleRate)
			:m_sampleRate(sampleRate), m_spectrum()
		{}

		MelFilter(const MelFilter& copy);

		MelFilter& operator=(const MelFilter& rhs);

		~MelFilter() {};

		void CreateFilter(int filterIndex, double melFilterWidth, int N);

		double Apply(const SpectrumType& dataSpectrum);

	private:
		void GenerateFilterSpectrum(double minFreq, double centerFreq, double maxFreq, int N);
	};
}

#endif
