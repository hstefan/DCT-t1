#ifndef HSTEFAN_LINEAR_GEN_HPP
#define HSTEFAN_LINEAR_GEN_HPP

#include <ctime>
#include <limits>
#include "SampleGenerator.hpp"

namespace hstefan
{
	namespace sample 
	{
		/*
		 * Gera amostra em progressao aritmetica, com valor inicial aleatorio e razao aleatoria.
		 */
		class LinearGen : public SampleGenerator
		{
		public:
			void generateSample(unsigned int n) 
			{
				const unsigned int max_rate = std::numeric_limits<signal_type>::max()/n;

				const signal_type rate = 1 + (signal_type) rand() % max_rate;
 				signal_type start = (signal_type)rand() % (std::numeric_limits<signal_type>::max() - n*rate);
				signal.resize(n);
				for(unsigned int i = 0; i < n; ++i)
				{
					signal[i] = start;
					start += rate;
				}
			}

		};
	} //namespace sample
} //namespace hstefan

#endif