#ifndef HSTEFAN_LINEAR_GEN_HPP
#define HSTEFAN_LINEAR_GEN_HPP

#include <ctime>
#include <limits>

namespace hstefan
{
	namespace sample 
	{
		class LinearGen : public SampleGenerator
		{
		public:
			void generateSample(unsigned int n) 
			{
				signal_type start = (signal_type)rand() % (std::numeric_limits<signal_type>::max() - n);
				signal.resize(n);
				signal[0] = start;
				for(unsigned int i = 1; i < n; i++) 
					signal[i] = start + i;
			}

		};
	} //namespace sample
} //namespace hstefan
#endif