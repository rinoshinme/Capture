#ifndef _WAV_IO_H
#define _WAV_IO_H

#include <fstream>
#include <string>
#include <cstring>
#include "wav_header.h"
#include "sound_obj.h"

namespace Capture
{
	class WAVReader
	{
	private:
		WavHeader header;
		std::ifstream fs;
		std::string filename;

	public:
		/* constructors and destructor */
		WAVReader(const std::string& fn)
			:filename(fn)
		{
			fs.open(filename.c_str(), std::ios::in | std::ios::binary);
		}

		// no copy constructor and copy assignment operator needed!!!

		~WAVReader()
		{
			fs.close();
		}

		// read into Sound object
		SoundObj Read()
		{
			fs.read((char*)&header, sizeof(WavHeader));
			SoundObj s(header.sampleRate, header.numChannels, header.bitsPerSample, header.subChunk2Size);
			char* data = s.GetPtrData();
			fs.read(data, header.subChunk2Size);

			return s;
		}

		long GetDataSize() const
		{
			return header.subChunk2Size;
		}

		short GetNumChannels() const
		{
			return header.numChannels;
		}

		long GetSampleRate() const
		{
			return header.sampleRate;
		}

		WavHeader GetHeader() const
		{
			return header;
		}
	};

	class WAVWriter
	{
	private:
		WavHeader header;
		std::ofstream fs;
		std::string filename;
		char* data;

	public:
		/* constructors and destructor */
		WAVWriter(const std::string& fn, const SoundObj& s)
			:filename(fn)
		{
			fs.open(filename, std::ios::out | std::ios::binary);
			// initialize header
			long dataSize = s.GetDataSize();
			short numChannels = s.GetNumChannels();
			long sampleRate = s.GetSampleRate();
			short bitsPerSample = s.GetBitsPerSample();

			//strcpy(header.RIFF, "RIFF");
			strcpy_s(header.RIFF, "RIFF");
			header.chunkSize = dataSize + 36;
			//strcpy(header.WAVE, "WAVE");
			strcpy_s(header.WAVE, "WAVE");
			//strcpy(header.FMT, "fmt ");
			strcpy_s(header.FMT, "FMT ");
			header.subChunk1Size = 16;
			header.audioFormat = 1;
			header.numChannels = numChannels;
			header.sampleRate = sampleRate;
			header.byteRate = bitsPerSample * numChannels * sampleRate / 8;
			header.blockAlign = (short)numChannels * bitsPerSample / 8;
			header.bitsPerSample = bitsPerSample;
			//strcpy(header.DATA, "data");
			strcpy_s(header.DATA, "DATA");
			header.subChunk2Size = dataSize;

			data = s.GetPtrData();
		}

		~WAVWriter()
		{
			fs.close();
		}

		void Write()
		{
			// write header
			fs.write((char*)&header, sizeof(WavHeader));

			// write data
			fs.write(data, header.subChunk2Size);
		}
	};

}

#endif

