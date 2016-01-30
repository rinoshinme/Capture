#include "SimpleWav.h"
#include <fstream>
#include <iostream>

namespace Capture
{
	SimpleSound WavRead(const std::string& filename, int ch)
	{
		std::ifstream fs;
		WavHeader header;
		fs.open(filename.c_str(), std::ios::binary | std::ios::in);
		// read all
		fs.read((char*)&header, sizeof(WavHeader));
		char* wavData = new char[header.subChunk2Size];
		fs.read(wavData, header.subChunk2Size);
		fs.close();

		long sampleRate = header.sampleRate;
		short numChannels = header.numChannels;
		long size = header.subChunk2Size;
		short bitsPerSample = header.bitsPerSample;

		long length = size * 8 / (numChannels * bitsPerSample);
		if (numChannels == 1 && ch == 1)
			ch = 0;
		double* soundData = new double[length];

		if (bitsPerSample == 8)
		{
			short step = numChannels;
			long maxValue = (1 << 7);
			for (long i = 0; i < length; ++i)
			{
				char value = wavData[i * step + ch];
				soundData[i] = value * 1.0 / maxValue;
			}
		}
		else
		{
			short step = static_cast<short>(numChannels * 2);
			long maxValue = (1 << 15);
			for (long i = 0; i < length; ++i)
			{
				char lo = wavData[i * step + 2 * ch + 0];
				char hi = wavData[i * step + 2 * ch + 1];
				soundData[i] = (lo + (hi << 8)) * 1.0 / maxValue;
			}
		}
		delete[] wavData;
		SimpleSound result(sampleRate, length, soundData);
		delete[] soundData;
		return result;
	}

	void WavWrite(const std::string& filename, const SimpleSound& sound, short bitsPerSample)
	{
		long size = sound.GetSize();
		long sampleRate = sound.GetSampleRate();
		short bytesPerSample = bitsPerSample / 8;

		char RIFF[] = "RIFF";
		char WAVE[] = "WAVE";
		char FMT[] = "fmt ";
		char DATA[] = "data";

		// prepare header
		WavHeader header;
		header.RIFF[0] = 'R';
		header.RIFF[1] = 'I';
		header.RIFF[2] = 'F';
		header.RIFF[3] = 'F';
		header.WAVE[0] = 'W';
		header.WAVE[1] = 'A';
		header.WAVE[2] = 'V';
		header.WAVE[3] = 'E';
		header.FMT[0] = 'f';
		header.FMT[1] = 'm';
		header.FMT[2] = 't';
		header.FMT[3] = ' ';
		header.DATA[0] = 'd';
		header.DATA[1] = 'a';
		header.DATA[2] = 't';
		header.DATA[3] = 'a';
		header.chunkSize = size * bytesPerSample + 36;
		header.subChunk1Size = 16;
		header.audioFormat = 1;
		header.numChannels = 1;
		header.sampleRate = sampleRate;
		header.byteRate = bytesPerSample * sampleRate;
		header.blockAlign = bytesPerSample;
		header.bitsPerSample = bitsPerSample;
		header.subChunk2Size = size;

		// prepare data
		char* wavData = new char[size * bytesPerSample];
		double* data = sound.GetPtrData();
		if (bitsPerSample == 8)
		{
			long maxValue = (1 << 7);
			for (long i = 0; i < size; ++i)
				wavData[i] = static_cast<char>(data[i] * maxValue);
		}
		else
		{
			long maxValue = (1 << 15);
			for (long i = 0; i < size; ++i)
			{
				int value = static_cast<int>(data[i] * maxValue);
				wavData[2 * i] = static_cast<char>(value & 0xFF);
				wavData[2 * i + 1] = static_cast<char>((value >> 8) & 0xFF);
			}
		}

		// write
		std::ofstream fs;
		try
		{
			fs.open(filename.c_str(), std::ios::out | std::ios::binary);
			fs.write((char*)&header, sizeof(WavHeader));
			fs.write(wavData, size * bytesPerSample);
		}
		catch (std::runtime_error)
		{
			std::cout << "write error" << std::endl;
		}
		fs.close();
		delete[] wavData;
	}
}

