#ifndef _SOUND_H
#define _SOUND_H

namespace Capture
{
	class Sound
	{
	private:
		long sampleRate;
		short numChannels;
		short bitsPerSample;
		long dataSize;
		char* data;

	public:
		/* constructors and destructor */
		Sound()
			:sampleRate(44100), numChannels(1), bitsPerSample(16), dataSize(0)
		{
			data = new char[dataSize];
		}

		// create from parameters, default data with all 0s
		Sound(long sr, short nc, short bps, long ds)
			:sampleRate(sr), numChannels(nc), bitsPerSample(bps), dataSize(ds)
		{
			data = new char[dataSize];
		}

		// create from existing data (double-precision floating point)
		Sound(long sr, short bps, double* mem, long size)
		{
			sampleRate = sr;
			numChannels = 1;
			bitsPerSample = bps;
			dataSize = size * bitsPerSample / 8;
			data = new char[dataSize];
			if (bitsPerSample == 8)
			{
				int maxValue = (1 << 7);
				for (int i = 0; i < size; ++i)
				{
					int value = static_cast<int>(mem[i] * maxValue);
					if (value < -maxValue)
						value = -maxValue;
					else if (value >= maxValue)
						value = maxValue - 1;
					data[i] = static_cast<char>(value);
				}
			}
			else
			{
				int maxValue = (1 << 15);
				for (int i = 0; i < size; ++i)
				{
					int value = static_cast<int>(mem[i] * maxValue);
					if (value < -maxValue)
						value = -maxValue;
					else if (value >= maxValue)
						value = maxValue - 1;
					
					data[2*i + 0] = static_cast<char>(value & 0xFF);
					data[2*i + 1] = static_cast<char>(value >> 8);
				}
			}
		}

		Sound(const Sound& copy)
		{
			sampleRate = copy.sampleRate;
			numChannels = copy.numChannels;
			bitsPerSample = copy.bitsPerSample;
			dataSize = copy.dataSize;
			data = new char[dataSize];
			memcpy(data, copy.data, dataSize);
		}

		~Sound()
		{
			delete[] data;
		}

		Sound& operator=(const Sound& rhs)
		{
			if (this == &rhs)
				return *this;
			sampleRate = rhs.sampleRate;
			numChannels = rhs.numChannels;
			bitsPerSample = rhs.bitsPerSample;
			dataSize = rhs.dataSize;
			delete[] data;
			data = new char[dataSize];
			memcpy(data, rhs.data, dataSize);

			return *this;
		}

		char* GetPtrData() const
		{
			return data;
		}

		long GetDataSize() const
		{
			return dataSize;
		}

		long GetSampleRate() const
		{
			return sampleRate;
		}

		short GetNumChannels() const
		{
			return numChannels;
		}

		short GetBitsPerSample() const
		{
			return bitsPerSample;
		}

		// non-trivial methods
		long GetNumSamples() const
		{
			return dataSize * 8 / (numChannels * bitsPerSample);
		}

		// memory should be pre-allocated
		// return false if error, true if success
		bool GetAllSamples16Bit(int ch, short* mem) const
		{
			if ((numChannels == 1 && ch == 1) || bitsPerSample == 8)
			{
				return false;
			}
			int numSamples = GetNumSamples();
			int step = numChannels * bitsPerSample / 8;
			for (int i = 0; i < numSamples; ++i)
			{
				char lo = data[i * step + 2 * ch];
				char hi = data[i * step + 2 * ch + 1];
				mem[i] = (lo + (hi << 8));
			}
			return true;
		}

		// memory should be pre-allocated
		bool GetAllSamples8Bit(int ch, char* mem) const
		{
			if ((numChannels == 1 && ch == 1) || bitsPerSample == 16)
				return false;
			int numSamples = GetNumSamples();
			int step = numChannels * bitsPerSample / 8;
			for (int i = 0; i < numSamples; ++i)
				mem[i] = data[i * step + ch];
			return true;
		}
		
		bool GetAllSamplesDouble(int ch, double* mem) const
		{
			if (numChannels == 1 && ch == 1)
				return false;
			int numSamples = GetNumSamples();
			int step = numChannels * bitsPerSample / 8;
			if (bitsPerSample == 8)
			{
				for (int i = 0; i < numSamples; ++i)
					mem[i] = data[i * step + ch] * 1.0 / 128;
			}
			else
			{
				for (int i = 0; i < numSamples; ++i)
				{
					char lo = data[i * step + 2 * ch];
					char hi = data[i * step + 2 * ch + 1];
					mem[i] = (lo + (hi << 8)) * 1.0 / (2 << 15);
				}
			}
			return true;
		}

		// create mono sound object (pick a single channel)
		Sound CreateMono16Bit(int ch)
		{
			if ((numChannels == 1 && ch == 1) || bitsPerSample == 8)
				throw (0);
			Sound result(sampleRate, 1, 16, dataSize / numChannels);
			GetAllSamples16Bit(ch, reinterpret_cast<short*>(result.GetPtrData()));
			return result;
		}

		Sound CreateMono8Bit(int ch)
		{
			if ((numChannels == 1 && ch == 1) || bitsPerSample == 8)
				throw (0);
			Sound result(sampleRate, 1, 8, dataSize / numChannels);
			GetAllSamples8Bit(ch, result.GetPtrData());
			return result;
		}

	};
}

#endif
