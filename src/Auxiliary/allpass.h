#ifndef _ALL_PASS_H
#define _ALL_PASS_H

namespace Capture
{
	class AllPass
	{
	private:
		double gain;
		int delay;
		int pos;

		double inputTemp;
		double outputTemp;

		double* inputBuffer;
		double* outputBuffer;

	public:
		/* constructors and destructor */
		AllPass(double g, int d)
			:gain(g), delay(d - 1)
		{
			inputBuffer = new double[d];
			outputBuffer = new double[d];
			Reset();
		}

		AllPass()
			:gain(1.0), delay(0)
		{
			inputBuffer = new double[0];
			outputBuffer = new double[0];
		}

		AllPass(const AllPass& copy)
		{
			gain = copy.gain;
			delay = copy.delay;
			pos = copy.pos;
			inputTemp = copy.inputTemp;
			outputTemp = copy.outputTemp;
			inputBuffer = new double[delay + 1];
			outputBuffer = new double[delay + 1];
			memcpy(inputBuffer, copy.inputBuffer, sizeof(double) * (delay + 1));
			memcpy(outputBuffer, copy.outputBuffer, sizeof(double) * (delay + 1));
		}

		AllPass& operator=(const AllPass& rhs)
		{
			if (this == &rhs)
				return *this;
			gain = rhs.gain;
			delay = rhs.delay;
			pos = rhs.pos;
			inputTemp = rhs.inputTemp;
			outputTemp = rhs.outputTemp;
			delete[] inputBuffer;
			inputBuffer = new double[delay + 1];
			memcpy(inputBuffer, rhs.inputBuffer, sizeof(double) * (delay + 1));
			delete[] outputBuffer;
			outputBuffer = new double[delay + 1];
			memcpy(outputBuffer, rhs.outputBuffer, sizeof(delay + 1));
		}

		~AllPass()
		{
			delete[] inputBuffer;
			delete[] outputBuffer;
		}

		double DoProcess(double input)
		{
			inputTemp = inputBuffer[pos];
			outputTemp = outputBuffer[pos];
			outputTemp = gain * input + inputTemp - gain * outputTemp;
			inputBuffer[pos] = input;
			outputBuffer[pos] = outputTemp;

			if (pos == delay)
				pos = 0;
			else
				pos++;
			return outputTemp;
		}

	private:
		void Reset()
		{
			for (pos = 0; pos <= delay; ++pos)
			{
				inputBuffer[pos] = 0;
				outputBuffer[pos] = 0;
			}
			pos = 0;
		}
	};
}


#endif

