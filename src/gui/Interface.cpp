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

         std::cout << "Trabalho 1 (Computacao Grafica)" << std::endl <<
            "Sobre a interface:" << std::endl <<
            "   Canvas superior: grafico da amostra de entrada" << std::endl << 
            "   Canvas inferior: grafico da saida da DCT" << std::endl <<
            "   Tabela: primeira linha representa os coeficientes de entrada e a segunda a saida da DCT" << std::endl <<
            "Geracao de amostra: pode-se gerar amostras utilizando o painel de baixo ou alterar os coeficientes diretamente na tabela." << std::endl <<
            "Observacoes: e' possivel observar os efeitos da alteracao dos coeficientes da DCT, o programa automaticamente aplicara a dct inversa e mostrara o sinal atualizado no canvas superior;" << std::endl <<
            "   Para truncar coeficientes, basta entrar com 0 na posicao desejada;" << std::endl << "   Ao passar o mouse sobre um vertice do grafico (quadrado), seu valor sera mostrado na tela." << std::endl;

         kernel->setWindowSize(W_WIDTH, W_HEIGHT);
         kernel->setWindowTitle("Discrete Cosine Transform - T1");

         kernel->run();
      }

   }//namespace gui
}//namespace hstefan