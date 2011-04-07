#ifndef HSTEFAN_INTERFACE_HPP
#define HSTEFAN_INTERFACE_HPP

#include <SCV/SCV.h>

namespace hstefan
{
	namespace gui
	{
		class Interface
		{
		public:
			Interface()
			{
				kernel = scv::Kernel::getInstance();
				color_scheme = scv::ColorScheme::getInstance();
				color_scheme->loadScheme(scv::ColorScheme::windows);
				kernel->setWindowSize(640, 480);
				kernel->setWindowTitle("Discrete Cosine Transform - T1");
				kernel->run();
			}

		private:
			scv::Kernel* kernel;
			scv::ColorScheme* color_scheme;
		};
	}
}

#endif