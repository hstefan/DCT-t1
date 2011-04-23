#include "Interface.hpp"
#include "../sample/LinearGen.hpp"
#include "../sample/RandomGen.hpp"
#include "../dct/DCT.hpp"
#include "DctController.hpp"

namespace hstefan
{
	namespace gui
	{
		Interface::Interface()
		{
			kernel = scv::Kernel::getInstance();
			color_scheme = scv::ColorScheme::getInstance();
			color_scheme->loadScheme(scv::ColorScheme::osx);
			
			sample::SampleGenerator* li = new sample::RandomGen();
			li->generateSample(16);

			std::vector<dct::DiscreteCosineTransform::output_type> coef = 
				dct::DiscreteCosineTransform::fdct(li->getSample());

			coef_tab = new CoefTable(scv::Point(8, 210), W_WIDTH, li->getSample(), coef);
			model = new DctModel(li->getSample());
			view = new DctView(scv::Point(10, 280), scv::Point(W_WIDTH - 10, 480), coef);
			controller = new DctController<CoefTable>(coef_tab, model, view);
			coef_tab->registerObserver(controller);
			coef_tab->notifyObservers();

			kernel->addComponent(view);
			kernel->addComponent(coef_tab);

			sample_panel = new SampleGenerationPanel(scv::Point(W_WIDTH/2 - 85, 520), 180, coef_tab);
			kernel->addComponent(sample_panel);

			kernel->setWindowSize(640, 620);
			kernel->setWindowTitle("Discrete Cosine Transform - T1");

			kernel->run();
		}

	}//namespace gui
}//namespace hstefan