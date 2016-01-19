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

