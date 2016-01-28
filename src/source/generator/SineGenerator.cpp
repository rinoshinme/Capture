#include "SineGenerator.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Capture
{
	void SineGenerator::Generate(long sampleCount)
	{
		data.resize(sampleCount);
		double normalizedFrequency = frequency / static_cast<double>(sampleRate);
		for (long i = 0; i < sampleCount; ++i)
		{
			data[i] = amplitude * std::sin(2.0 * M_PI * normalizedFrequency * i + phase * 2.0 * M_PI);
		}
	}

}