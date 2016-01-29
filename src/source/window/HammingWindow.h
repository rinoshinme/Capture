#ifndef _HAMMING_WINDOW_H
#define _HAMMING_WINDOW_H

#include "window.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Capture
{
	class HammingWindow: public Window
	{
	public:
		HammingWindow()
		{}

		HammingWindow(int size)
			:Window()
		{
			Generate(size);
		}

		void Generate(int size)
		{
			m_data.resize(size);
			for (int i = 0; i < size; ++i)
				m_data[i] = 0.53836 - 0.46164 * cos(2.0 * M_PI * i / double(size - 1));
		}
	};
}

#endif
