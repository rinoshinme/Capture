#ifndef _GENERATOR_H
#define _GENERATOR_H

#include <vector>

namespace Capture
{
	// base class for various signal generators
	class Generator
	{
	protected:
		long sampleRate;
		double frequency;
		double phase;
		double amplitude;
		std::vector<double> data;

	public:
		/* constructors and destructor */
		Generator()
			:sampleRate(44100), frequency(0.0), phase(0.0), amplitude(1.0)
		{}

		Generator(long sr, double f, double ph, double amp)
			:sampleRate(sr), frequency(f), phase(ph), amplitude(amp)
		{}

		virtual ~Generator() {}

		// methods
		Generator& SetFrequency(double f)
		{
			frequency = f;
			return *this;
		}

		Generator& SetAmplitude(double amp)
		{
			amplitude = amp;
			return *this;
		}

		Generator& SetPhase(double ph)
		{
			phase = ph;
			return *this;
		}

		virtual const double* ToArray() const
		{
			return &data[0];
		}

		virtual void Generate(long sampleCount) = 0;
	};
}

#endif
