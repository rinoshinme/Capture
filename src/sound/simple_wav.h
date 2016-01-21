#ifndef _SIMPLE_WAV_H
#define _SIMPLE_WAV_H

#include <string>
#include "wav_header.h"

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
			:sampleRate(0), size(0), data(NULL)
		{}

		SimpleSound(long sr, long sz)
			:sampleRate(sr), size(sz)
		{
			data = new double[size];
		}

		SimpleSound(long sr, long sz, double* d)
			:sampleRate(sr), size(sz)
		{
			data = new double[size];
			memcpy(data, d, sizeof(double) * size);
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

	// simple interface to read and write wav files

	SimpleSound WavRead(const std::string& filename, int ch);

	void WavWrite(const std::string& filename, const SimpleSound& sound, short bitsPerSample);
}


#endif

