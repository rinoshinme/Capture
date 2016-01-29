#ifndef _GAUSSIAN_WINDOW_H
#define _GAUSSIAN_WINDOW_H

#include "window.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Capture
{
	class GaussianWindow: public Window
	{
	private:
		double sigma; // sigma = std / (size-1)/2
	public:
		GaussianWindow()
		{}

		GaussianWindow(int size, double s)
			:sigma(s)
		{
			Generate(size);
		}

		void Generate(int size)
		{
			m_data.resize(size);
			for (int i = 0; i < size; ++i)
				m_data[i] = exp((-0.5) * pow((i - (size - 1.0) / 2.0)/(sigma * (size - 1.0) / 2.0), 2.0));
		}
	};
}

#endif
