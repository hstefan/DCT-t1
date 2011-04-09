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
			
			
			kernel->setWindowSize(640, 480);
			kernel->setWindowTitle("Discrete Cosine Transform - T1");

			sample::SampleGenerator* li = new sample::RandomGen();
			li->generateSample(16);
			std::vector<unsigned char>& f = li->getSample();
			std::vector<double>& out = dct::DiscreteCosineTransform::fdct(f);
			dct_canvas->setCoeficents(out);

			kernel->run();
		}

	}//namespace gui
}//namespace hstefan