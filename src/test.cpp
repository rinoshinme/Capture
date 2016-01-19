#include <iostream>
#include <string>
#include "wav_io.h"
#include "sound.h"
#include "random.h"

#include "Auxiliary\delay.h"
#include "Auxiliary\allpass.h"
#include "Auxiliary\nested_allpass.h"

using namespace Capture;

void TestWAV()
{
	std::string infile("E:\\Projects\\Sparks Fly.wav");
	std::string outfile("E:\\Projects\\Sparks Fly3.wav");
	WAVReader reader(infile);
	Sound s = reader.Read();

	// read double precision and write to file
	int numSamples = s.GetNumSamples();
	double* data = new double[numSamples];
	s.GetAllSamplesDouble(0, data);

	Sound s3(44100, 16, data, numSamples);
	WAVWriter writer(outfile, s3);
	writer.Write();

	delete[] data;
}

void TestRandom()
{
	std::string outfile("E:\\Projects\\random.wav");
	double* d = new double[44100];
	for (int i = 0; i < 44100; ++i)
		d[i] = RandomDouble();
	Sound s(44100, 8, d, 44100);
	WAVWriter writer(outfile, s);
	writer.Write();
}

void TestAux()
{
	std::string infile("E:\\Projects\\Sparks Fly.wav");
	std::string outfile("E:\\Projects\\Sparks Fly3.wav");
	WAVReader reader(infile);
	Sound s = reader.Read();
	Sound s2 = s.CreateMono16Bit(0);

	int num = s2.GetNumSamples();
	double* data = new double[num];
	s2.GetAllSamplesDouble(0, data);
	
	int numDelay = 1000;
	double gain = 0.6;
	int size = 1000000;

	//Delay delay(numDelay);
	//AllPass allPass(gain, numDelay);
	//NestedAllPass aux(gain, gain, numDelay, numDelay * 2);
	DoubleNestedAllPass aux(gain, gain/2, 0.9, numDelay/2, numDelay, numDelay*2);
	double* result = new double[size];
	for (int i = 0; i < size; ++i)
		result[i] = aux.DoProcess(data[i]);

	Sound s3(44100, 16, result, size);
	WAVWriter writer(outfile, s3);
	writer.Write();
}

int main()
{
	// TestWAV();
	// TestRandom();

	TestAux();

	std::cout << "Finished..." << std::endl;
	std::getchar();
	return 0;
}
