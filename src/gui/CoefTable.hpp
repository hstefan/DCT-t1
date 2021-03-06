#ifndef HSTEFAN_COEF_TABLE_HPP
#define HSTEFAN_COEF_TABLE_HPP

#include <SCV/Table.h>
#include "../dct/DCT.hpp"
#include <sstream>
#include <stack>
#include "SCV/Point.h"
#include <SCV/TextField.h>
#include "../util/Observable.hpp"

namespace hstefan
{
   namespace gui
   {
      /**
      * Tabela para visualiza��o e altera��o dos coeficientes de saida.
      */
      class CoefTable : public scv::Table, public util::Observable
      {
      public:
         typedef dct::DiscreteCosineTransform::output_type output_type;
         typedef dct::DiscreteCosineTransform::signal_type signal_type;

         static const int SAMPLE_ROW_NUMBER = 0;
         static const int COEF_ROW_NUMBER = 1;

         /**
         * @param pos Posi��o da Table na janela.
         * @param width Largura da janela.
         * @param signal_row Coeficientes de entrada (linha sample).
         * @param output_row Coeficientes de saidada DCT (linha DCT).
         */
         CoefTable(const scv::Point& pos, unsigned int width, const std::vector<signal_type>& signal_row,
            const std::vector<output_type>& output_row);

         /**
         * Atualiza os valores no canvas.
         */
         virtual void onKeyUp(const scv::KeyEvent &evt );

         /**
         * Overload da fun��o processKey, apenas corrige o bug das callbacks de teclado e chama a fun��o original.
         */
         virtual void processKey(const scv::KeyEvent &evt);

         /**
         * Faz com que as callbacks de mouse sejam chamadas e chama a fun��o original.
         */
         virtual void processMouse(const scv::MouseEvent &evt);

         inline const std::vector<output_type>& getCoefficients() const
         {
            return coef_vec;
         }

         inline const std::vector<signal_type>& getSignal() const
         {
            return signal_vec;
         }

         /**
         * Realiza a��es necess�rias para o bom funcionamente do programa quando a linha de amostras for alterada.
         */
         void onSampleRowChange(const scv::KeyEvent& evt, unsigned int cel_number);

         /**
         * Realiza a��es necess�rias para o bom funcionamente do programa quando a linha de coeficientes da DCT for alterada.
         */
         void onCoefficientsRowChange(const scv::KeyEvent& evt, unsigned int cel_number);

         void onSampleRowChange();

         void setCoefficientstRow(const std::vector<output_type>& dct_row);
         void setSampleRow(const std::vector<signal_type>& signal_row);

      private:
         /**
          * Normaliza a linha de amostra, para que n�o haja valores de sinal maiores que o permitido (0,255)
          */
         void normalizeSampleRow();

         /**
          * Redimensiona a tabela (tornando os campos extra n�o editaveis)
          * Exemplificando, caso tenhamos 16 colunas mas apenas 8 valores, os primeiros 8 campos manter�o-se "normais" 
          * e os outros ser�o bloqueados para edi��o e exibir�o uma string vazia. 
          */
         void resizeTable();

         std::vector<output_type> coef_vec;
         std::vector<signal_type> signal_vec; 
         scv::TextFilter uinteger_filter;
         scv::TextFilter double_filter;
      };
   }//namespace gui
}//namespace hstefan

#endif