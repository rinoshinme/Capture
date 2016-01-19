#ifndef _NESTED_ALL_PASS_H
#define _NESTED_ALL_PASS_H

#include "allpass.h"
#include "delay.h"

namespace Capture
{
	class NestedAllPass
	{
	private:
		AllPass allPass;
		Delay delay;
		double temp;
		double gain;
		double tempAllPass;

	public:
		/* constructors and destructor */
		NestedAllPass(double g1, double g2, int d1, int d2)
			:gain(g2), temp(0.0), allPass(g1, d1), delay(d2)
		{}

		double DoProcess(double input)
		{
			tempAllPass = allPass.DoProcess(input + gain * temp);
			temp = delay.DoProcess(tempAllPass)  - gain * input;
			return temp;
		}
	};


	class DoubleNestedAllPass
	{
	private:
		AllPass allPass1;
		AllPass allPass2;
		Delay delay;

		double temp;
		double gain;
		double tempAllPass;

	public:
		/* constructors and destructor */
		DoubleNestedAllPass(double g1, double g2, double g3, int d1, int d2, int d3)
			:gain(g3), temp(0.0), allPass1(g1, d1), allPass2(g2, d2), delay(d3)
		{}

		double DoProcess(double input)
		{
			tempAllPass = allPass1.DoProcess(input + gain * temp);
			tempAllPass = allPass2.DoProcess(tempAllPass);
			temp = delay.DoProcess(tempAllPass);
			return temp;
		}

	};
}




#endif

