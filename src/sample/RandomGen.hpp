#ifndef HSTEFAN_RANDOM_GEN_HPP
#define HSTEFAN_RANDOM_GEN_HPP

#include "SampleGenerator.hpp"
#include <ctime>
#include <cstdlib>

namespace hstefan 
{
	namespace sample 
	{
		class RandomGen : public SampleGenerator
		{
		public:
			inline void generateSample(unsigned int n)
			{
				signal.clear();
				signal.resize(n);
			
				for(unsigned int i = 0; i < n; ++i) 
					signal[i] = (double)rand() / RAND_MAX;
			}
		};
	}//namespace sample
} //namespace sample

#endif