#ifndef _GARDNER_REVERB_H
#define _GARDNER_REVERB_H

#include <math.h>
#include "delay.h"
#include "allpass.h"
#include "nested_allpass.h"

#define PI 3.1415926

namespace Capture
{
	class SmallGardnerReverb
	{
	private:
		Delay delay;
		DoubleNestedAllPass allPass1;
		NestedAllPass allPass2;

		double gain;
		double tempDelay;
		double tempAllPass1;
		double tempAllPass2;
		double tempLowPass;
		double lpGain;

	public:
		/* constructors and destuctor */
		SmallGardnerReverb(double g)
		{
			gain = g;
			tempLowPass = 0.0;
			delay = Delay(1058);
			allPass1 = DoubleNestedAllPass(0.4, 0.6, 0.3, 970, 366, 1543);
			allPass2 = NestedAllPass(0.4, 0.1, 1323, 2910);

			tempAllPass1 = 0.0;
			tempAllPass2 = 0.0;
			tempLowPass = 0.0;
			
			double temp = cos(2 * PI * (4200.0) / 44100);
			lpGain = 2 - temp - sqrt((temp - 2) * (temp - 2) - 1);
		}

		double DoProcess(double input)
		{
			tempDelay = delay.DoProcess(input + gain * tempLowPass);
			tempAllPass1 = allPass1.DoProcess(tempDelay);
			tempAllPass2 = allPass2.DoProcess(tempAllPass1);
			tempLowPass = (1 - lpGain) * tempAllPass2 + lpGain * tempLowPass;
			return tempAllPass1 + tempAllPass2;
		}
	};

	class MediumGardnerReverb
	{
	private:
		DoubleNestedAllPass allPass1;
		Delay delay1;
		AllPass allPass2;
		Delay delay2;
		Delay delay3;
		NestedAllPass allPass3;
		Delay delay4;

		double gain;
		double tempAllPass1;
		double tempDelay2;
		double tempAllPass3;
		double tempDelay4;
		double tempLowPass;
		double lpGain;

	public:
		MediumGardnerReverb(double g)
			:gain(g), tempLowPass(0.0),
			allPass1(0.7, 0.5, 0.3, 970, 366, 1543),
			delay1(220),
			allPass2(0.5, 1323),
			delay2(2954),
			delay3(661),
			allPass3(0.6, 0.3, 432, 1719),
			delay4(661)
		{
			double temp = cos(2 * PI * (2500.0 / 44100));
			lpGain = 2 - temp - sqrt((temp - 2) * (temp - 2) - 1);
		}

		double DoProcess(double input)
		{
			tempAllPass1 = allPass1.DoProcess(input + gain * tempLowPass);
			tempDelay2 = delay2.DoProcess(allPass2.DoProcess(delay1.DoProcess(tempAllPass1)));
			tempAllPass3 = allPass3.DoProcess((gain * delay3.DoProcess(tempDelay2)) + input);
			tempDelay4 = delay4.DoProcess(tempAllPass3);
			tempLowPass = (1 - lpGain) * tempDelay4 + lpGain * tempLowPass;

			return tempAllPass1 + tempDelay2 + tempAllPass3;
		}
	};

	class LargeGardnerReverb
	{
	private:
		AllPass allPass1;
		AllPass allPass2;
		Delay delay1;
		Delay delay2;
		NestedAllPass allPass3;
		Delay delay3;
		Delay delay4;
		DoubleNestedAllPass allPass4;

		double gain;
		double tempDelay1;
		double tempDelay3;
		double tempAllPass3;
		double tempLowPass;
		double lpGain;

	public:
		LargeGardnerReverb(double g)
			:gain(g), tempLowPass(0.0),
			allPass1(0.3, 352),
			allPass2(0.3, 529),
			delay1(176),
			delay2(749),
			allPass3(0.25, 0.5, 2734, 3826),
			delay3(1367),
			delay4(661),
			allPass4(0.25, 0.25, 0.5, 3351, 1323, 5292)
		{
			double temp = cos(2 * PI * (2600.0 / 44100));
			lpGain = 2 - temp - sqrt((temp - 2) * (temp - 2) - 1);
		}

		double DoProcess(double input)
		{
			tempDelay1 = delay1.DoProcess(allPass2.DoProcess(allPass1.DoProcess(input + gain * tempLowPass)));
			tempDelay3 = delay3.DoProcess(allPass3.DoProcess(delay2.DoProcess(tempDelay1)));
			tempAllPass3 = allPass4.DoProcess(delay4.DoProcess(tempDelay3));
			tempLowPass = (1 - lpGain) * tempAllPass3 + lpGain * tempLowPass;
			return 0.32 * tempDelay1 + 0.14 * tempDelay3 + 0.14 * tempAllPass3;
		}
	};
}


#endif

