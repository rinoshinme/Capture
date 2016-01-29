#ifndef _RECTANGULAR_WINDOW_H
#define _RECTANGULAR_WINDOW_H

#include "window.h"

namespace Capture
{
	class RectangularWindow: public Window
	{
	public:
		RectangularWindow()
		{}

		RectangularWindow(int size)
			:Window()
		{
			Generate(size);
		}

		void Generate(int size)
		{
			m_data.resize(size);
			for (int i = 0; i < size; ++i)
				m_data[i] = 1.0;
		}
	};
}

#endif
