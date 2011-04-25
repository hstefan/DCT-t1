#ifndef HSTEFAN_DCT_CONTROLLER_HPP
#define HSTEFAN_DCT_CONTROLLER_HPP

#include "DctView.hpp"
#include "DctModel.hpp"
#include "../util/Listener.hpp"
#include "CoefTable.hpp"

namespace hstefan
{
   namespace gui
   {
      template <class T = CoefTable>
      class DctController : public util::Listener
      {
      public:
         typedef DctModel::output_type output_type;
         typedef DctModel::signal_type signal_type;

         /*
          * @param observing ponteiro para o objeto que está sendo observado pelo controlador.
          * @param model modelo usado para plotar o gráfico.
          * @param view "canvas" que plota o grafico da saída da dct.
          * @param sig_view "canvas" que plota o grafico do sinal de entrada.
          */
         DctController(T* observing, DctModel* model, DctView<output_type>* view, DctView<signal_type>* sig_view);

         virtual void notify();
      private:
         DctModel* model;
         DctView<output_type>* view;
         DctView<signal_type>* sig_view;
         T* observing;
      };

      template <class T>
      DctController<T>::DctController(T* observing, DctModel* model, DctView<output_type>* view, DctView<signal_type>* sig_view)
         : model(model), view(view), observing(observing), sig_view(sig_view)
      {}

      template <class T>
      void DctController<T>::notify()
      {
         std::vector<signal_type> sig(observing->getSignal());
         if(sig != model->signal()) //indica que a amostra armazenada no modelo não está em sincronia com o do objeto observado.
         {
            sig_view->setCoefficients(sig);
            model->setSignal(sig);
            view->setCoefficients(model->coefficients());
            observing->setCoefficientstRow(model->coefficients());
         }
         else //indica que houve mudancas nos COEFICIENTES
         {
            std::vector<output_type> out = observing->getCoefficients();
            if(out != model->coefficients())
            {
               model->setOutput(out);
               view->setCoefficients(model->coefficients());
               sig_view->setCoefficients(model->signal());
               observing->setSampleRow(model->signal());
            }
         }
      }
   }
}

#endif