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
		Delay(int d=0)
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

		Delay(const Delay& copy)
		{
			pos = copy.pos;
			delay = copy.delay;
			temp = copy.temp;
			if (!copy.delayBuffer)
				delayBuffer = NULL;
			else
			{
				delayBuffer = new double[delay + 1];
				Reset();
			}
		}

		~Delay()
		{
			if (delayBuffer)
				delete[] delayBuffer;
		}

		Delay& operator=(const Delay& rhs)
		{
			if (this == &rhs)
				return *this;
			pos = rhs.pos;
			delay = rhs.delay;
			temp = rhs.temp;
			if (delayBuffer)
				delete[] delayBuffer;
			if (!rhs.delayBuffer)
				delayBuffer = NULL;
			else
			{
				delayBuffer = new double[delay + 1];
				memcpy(delayBuffer, rhs.delayBuffer, sizeof(double) * (delay + 1));
			}
			return *this;
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

