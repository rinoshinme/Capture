#include "WhiteNoiseGenerator.h"
#include "../../functions.h"

namespace Capture
{
	void WhiteNoiseGenerator::Generate(long sampleCount)
	{
		data.resize(sampleCount);
		for (long i = 0; i < sampleCount; ++i)
			data[i] = amplitude * (RandomDouble() - 0.5) * 2;
	}
}
