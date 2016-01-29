#ifndef _SINE_GENERATOR_H
#define _SINE_GENERATOR_H

#include "Generator.h"

namespace Capture
{
	class SineGenerator: public Generator
	{
	public:
		SineGenerator()
			:Generator()
		{}

		SineGenerator(long sr, double f)
			:Generator(sr, f, 0.0, 1.0)
		{}

		virtual void Generate(long sampleCount);
	};
}

#endif
