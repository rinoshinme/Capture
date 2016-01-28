#ifndef _SQUARE_GENERATOR_H
#define _SQUARE_GENERATOR_H

#include "Generator.h"

namespace Capture
{
	class SquareGenerator: public Generator
	{
	private:
		double duty;
		
	public:
		/* constructors and destructor */
		SquareGenerator()
			:Generator(), duty(0.5)
		{}

		SquareGenerator(long sr, double f, double d=0.5)
			:Generator(sr, f, 0.0, 0.0), duty(d)
		{}

		virtual void Generate(long sampleRate);

		SquareGenerator& SetDuty(double d)
		{
			duty = d;
			return *this;
		}
	};
}

#endif
