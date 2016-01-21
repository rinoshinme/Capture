#if 0
#include <iostream>
#include <string>

#include "Auxiliary\delay.h"
#include "Auxiliary\allpass.h"
#include "Auxiliary\nested_allpass.h"
#include "Auxiliary\gardner_reverb.h"

#include "utils\helper.h"
#include "filter\firfilter.h"
#include "filter\iirfilter.h"
#include "sound.h"

using namespace Capture;

void TestSimpleWav()
{
	std::string infile("E:\\Projects\\Sparks Fly.wav");
	std::string outfile("E:\\Projects\\Sparks Fly3.wav");
	SimpleSound s = WavRead(infile, 0);

	double* data = s.GetPtrData();
	
	for (int i = 0; i < 1000; ++i)
		std::cout << data[100000 + i] << std::endl;
	//SimpleSound s2(s.GetSampleRate(), 1000000, data);
	//WavWrite(outfile, s2, 16);
}

void TestPower()
{
	for (long i = 4; i <= 16; ++i)
		std::cout << Power2(i) << std::endl;

	std::cout << Power2(2);
}

void TestFirFilter()
{
	double input[] = {0, 1, 2, 3, 4, 5, 6, 7};
	double a[] = {0.5, 0.5};
	FirFilter filter(a, 2);

	double output[] = {0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 8; ++i)
	{
		output[i] = filter.DoProcess(input[i]);
		std::cout << output[i] << std::endl;
	}
}

void TestIirFilter()
{
	double input[] = {0, 1, 2, 3, 4, 5, 6, 7};
	double alpha = 0.5;
	double a[] = {alpha};
	double b[] = {1 - alpha};
	IirFilter filter(a, b, 1, 1);

	double output[] = {0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 8; ++i)
	{
		output[i] = filter.DoProcess(input[i]);
		std::cout << output[i] << std::endl;
	}
}

int main()
{
	TestSimpleWav();
	// TestPower();
	// TestFirFilter();
	// TestIirFilter();
	std::cout << "Finished..." << std::endl;
	std::getchar();
	return 0;
}

#endif
