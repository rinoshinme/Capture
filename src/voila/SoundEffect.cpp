#include "SoundEffect.h"

namespace Capture
{
	SimpleSound VocalRemoving(SimpleSound channelLeft, SimpleSound channelRight)
	{
		long sampleRate = channelLeft.GetSampleRate();
		long size = channelLeft.GetSize();

		double* data = new double[size];
		double* chleft = channelLeft.GetPtrData();
		double* chright = channelRight.GetPtrData();

		for (int i = 0; i < size; ++i)
			data[i] = (chleft[i] - chright[i]) / 2;

		SimpleSound result(sampleRate, size, data);
		delete[] data;
		return result;
	}

	SimpleSound Mix(SimpleSound sound1, SimpleSound sound2)
	{
		long sampleRate = sound1.GetSampleRate();
		long size = sound1.GetSize();

		double* data = new double[size];

		double* ch1 = sound1.GetPtrData();
		double* ch2 = sound2.GetPtrData();

		for (int i = 0; i < size; ++i)
		{
			double sum = ch1[i] + ch2[i];
			data[i] = Saturation(sum);
		}
		SimpleSound result(sampleRate, size, data);
		delete[] data;
		return result;
	}
}
