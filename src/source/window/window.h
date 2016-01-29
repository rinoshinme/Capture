#ifndef _WINDOW_WINDOW_H
#define _WINDOW_WINDOW_H

#include <vector>

namespace Capture
{
	class Window
	{
	protected:
		std::vector<double> m_data;
	public:
		/* constructors and destructor */
		Window()
		{}

		virtual ~Window()
		{}

		// methods 
		int GetSize() const
		{
			return m_data.size();
		}

		double operator[](int index) const
		{
			return m_data[index];
		}

		virtual void Generate(int size) = 0;
	};

}

#endif
