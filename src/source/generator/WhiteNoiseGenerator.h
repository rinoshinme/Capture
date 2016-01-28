#ifndef _WHITE_NOISE_GENERATOR_H
#define _WHITE_NOISE_GENERATOR_H

#include "Generator.h"

namespace Capture
{
	class WhiteNoiseGenerator: public Generator
	{
		WhiteNoiseGenerator()
			:Generator()
		{}

		WhiteNoiseGenerator(long sr)
			:Generator(sr, 0.0, 0.0, 1.0)
		{}

		virtual void Generate(long sampleCount);
	};
}

#endif
