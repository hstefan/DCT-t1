#include "Interface.hpp"
#include "../sample/LinearGen.hpp"
#include "../sample/RandomGen.hpp"
#include "../dct/DCT.hpp"

namespace hstefan
{
	namespace gui
	{
		Interface::Interface()
		{
			kernel = scv::Kernel::getInstance();
			color_scheme = scv::ColorScheme::getInstance();
			
			dct_canvas = new DctCanvas(W_WIDTH);
			color_scheme->loadScheme(scv::ColorScheme::windows);
			kernel->addComponent(dct_canvas);

			sample::SampleGenerator* li = new sample::RandomGen();
			li->generateSample(16);
			std::vector<unsigned char>& f = li->getSample();
			std::vector<double>& out = dct::DiscreteCosineTransform::fdct(f);
			dct_canvas->setCoeficents(out);

			coef_tab = new CoefTable(16, dct::DiscreteCosineTransform::fdct(f), 
				scv::Point(10, dct_canvas->getHeight() + 10), W_WIDTH);
			kernel->addComponent(coef_tab);

			kernel->setWindowSize(640, 480);
			kernel->setWindowTitle("Discrete Cosine Transform - T1");

			kernel->run();
		}

	}//namespace gui
}//namespace hstefan