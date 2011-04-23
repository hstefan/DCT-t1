#ifndef HSTEFAN_EQUAL_VALUES_GEN_HPP
#define HSTEFAN_EQUAL_VALUES_GEN_HPP

#include "SampleGenerator.hpp"
#include <cstdlib>
#include <limits>

namespace hstefan
{
   namespace sample
   {
      class EqualValuesGen : public SampleGenerator
      {
         virtual void generateSample(unsigned int n) 
         {
            signal.resize(n);
            signal.clear();
            signal.insert(signal.begin(), n, rand() % std::numeric_limits<signal_type>::max());
         }

      };
   }
}
#endif