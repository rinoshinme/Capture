#ifndef _DELAY_H
#define _DELAY_H

namespace Capture
{
	class Delay
	{
	private:
		double* delayBuffer;
		int pos;
		int delay;
		double temp;

	public:
		/* constructors and destructor */
		Delay(int d)
		{
			if (d == 0)
			{
				delay = 0;
				delayBuffer = NULL;
			}
			else
			{
				delay = d -1;
				delayBuffer = new double[d];
				Reset();
			}
		}

		~Delay()
		{
			if (delayBuffer)
				delete[] delayBuffer;
		}

		double DoProcess(double input)
		{
			if (delay == 0)
				return input;
			else
			{
				temp = delayBuffer[pos];
				delayBuffer[pos] = input;
				if (pos == delay)
					pos = 0;
				else
					pos++;
				return temp;
			}
		}

	private:
		void Reset()
		{
			if (delayBuffer)
			{
				for (pos = 0; pos <= delay; ++pos)
					delayBuffer[pos] = 0;
				pos = 0;
			}
		}
	};
}

#endif

