#ifndef HSTEFAN_DCT_HPP
#define HSTEFAN_DCT_HPP

#include <vector>

namespace hstefan
{
   namespace dct
   {
      /**
      * Classe usada para aplicar a DCT e IDCT em uma dada entrada.
      */
      class DiscreteCosineTransform
      {
      public:
         typedef unsigned char signal_type;
         typedef double output_type;

         /**
         * Aplica a DCT sobre uma entrada.
         * @param sample Amostra para aplicar DCT.
         * @return vector com os coeficientes gerados pela DCT.
         */
         static std::vector<output_type> fdct(const std::vector<signal_type>& sample);

         /**
         * Aplica a DCT inversa sobre uma entrada.
         * @param coef Coeficientes que se deseja aplicar a DCT inversa. 
         * @return vector com o valor original dos coeficienes.
         */
         static std::vector<signal_type> idct(const std::vector<output_type>& coef);
      };
   }
}

#endif