#ifndef _WAV_HEADER_H
#define _WAV_HEADER_H

namespace Capture
{
	struct WavHeader
	{
		char RIFF[4];
		long chunkSize;
		char WAVE[4];
		char FMT[4];
		long subChunk1Size;
		short audioFormat;
		short numChannels;
		long sampleRate;
		long byteRate;
		short blockAlign;
		short bitsPerSample;
		char DATA[4];
		long subChunk2Size;
	};
}



#endif

