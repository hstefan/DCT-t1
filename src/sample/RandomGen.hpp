#ifndef HSTEFAN_RANDOM_GEN_HPP
#define HSTEFAN_RANDOM_GEN_HPP

#include "SampleGenerator.hpp"
#include <ctime>
#include <cstdlib>
#include <limits>

namespace hstefan 
{
   namespace sample 
   {
      /*
      * Gera uma amostra composta por numeros aleatorios.
      */
      class RandomGen : public SampleGenerator
      {
      public:
         inline void generateSample(unsigned int n)
         {
            signal.clear();
            signal.resize(n);

            for(unsigned int i = 0; i < n; ++i) 
               signal[i] = (signal_type) rand() % std::numeric_limits<signal_type>::max();
         }
      };
   }//namespace sample
} //namespace sample

#endif