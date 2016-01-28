#include "SquareGenerator.h"

namespace Capture
{
	void SquareGenerator::Generate(long sampleCount)
	{
		data.resize(sampleCount);
		long samplesPerPeriod = static_cast<long>(static_cast<double>(sampleRate) / frequency);
		long positiveLength = static_cast<long>(duty * samplesPerPeriod);
		for (long i = 0; i < sampleCount; ++i)
		{
			long index = i % samplesPerPeriod;
			data[i] = ((index < positiveLength) ? 1 : -1) * amplitude;
		}
	}
}
