#ifndef _SIMPLE_WAV_H
#define _SIMPLE_WAV_H

#include <string>
#include "WavHeader.h"

namespace Capture
{
	// a sound class contain double precision mono channel audio data
	class SimpleSound
	{
	private:
		long sampleRate;
		long size;
		double* data;

	public:
		SimpleSound()
			:sampleRate(0), size(0)
		{
			data = new double[0]; // dummy data
		}

		SimpleSound(long sr, long sz, double* d=NULL)
			:sampleRate(sr), size(sz)
		{
			data = new double[size];
			if (d)
				memcpy(data, d, sizeof(double) * size);
			else
				memset(data, 0, sizeof(double) * size);
		}

		SimpleSound(const SimpleSound& copy)
		{
			sampleRate = copy.sampleRate;
			size = copy.size;
			data = new double[size];
			memcpy(data, copy.data, sizeof(double) * size);
		}

		~SimpleSound()
		{
			if (data)
				delete[] data;
		}

		SimpleSound& operator=(const SimpleSound& rhs)
		{
			if (this == &rhs)
				return *this;
			sampleRate = rhs.sampleRate;
			size = rhs.size;
			delete[] data;
			data = new double[size];
			memcpy(data, rhs.data, sizeof(double) * size);
			return *this;
		}

		// methods
		double* GetPtrData() const
		{
			return data;
		}

		double GetValue(long index) const
		{
			return data[index];
		}

		void SetValue(long index, double value)
		{
			data[index] = value;
		}

		long GetSize() const
		{
			return size;
		}

		long GetSampleRate() const
		{
			return sampleRate;
		}
	};

	SimpleSound WavRead(const std::string& filename, int ch);

	void WavWrite(const std::string& filename, const SimpleSound& sound, short bitsPerSample);
}

#endif
