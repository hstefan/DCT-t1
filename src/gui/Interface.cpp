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

         coef_tab = new CoefTable(scv::Point(12, 220), W_WIDTH, li->getSample(), coef);
         model = new DctModel(li->getSample());
         view = new DctView<output_type>(scv::Point(10, 290), scv::Point(W_WIDTH - 10, 490), coef);


         sig_view = new DctView<signal_type>(scv::Point(10, 10), scv::Point(W_WIDTH - 10, 210), li->getSample(), false);

         controller = new DctController<CoefTable>(coef_tab, model, view, sig_view);
         coef_tab->registerObserver(controller);
         coef_tab->notifyObservers();

         kernel->addComponent(view);
         kernel->addComponent(coef_tab);

         sample_panel = new SampleGenerationPanel(scv::Point(W_WIDTH/2 - 86, 500), 175, coef_tab);
         kernel->addComponent(sample_panel);
         kernel->addComponent(sig_view);
         kernel->addComponent(sig_view->getLabel());
         kernel->addComponent(view->getLabel());

         kernel->setWindowSize(W_WIDTH, 590);
         kernel->setWindowTitle("Discrete Cosine Transform - T1");

         kernel->run();
      }

   }//namespace gui
}//namespace hstefan