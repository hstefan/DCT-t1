#ifndef HSTEFAN_LINEAR_GEN_HPP
#define HSTEFAN_LINEAR_GEN_HPP

#include <ctime>
#include <limits>

namespace hstefan
{
	namespace sample 
	{
		/*
		 * Gera amostra em progressao aritmetica, com valor inicial aleatorio e razao aleatoria (entre 1 e 20)
		 */
		class LinearGen : public SampleGenerator
		{
		private:
			static const int MAX_RATE = 20;
		public:
			void generateSample(unsigned int n) 
			{
				const signal_type rate = (signal_type) rand() % MAX_RATE;
 				signal_type start = (signal_type)rand() % (std::numeric_limits<signal_type>::max() - n - MAX_RATE);
				signal.resize(n);
				signal[0] = start;
				for(unsigned int i = 1; i < n; ++i) 
					signal[i] = start + i;
			}

		};
	} //namespace sample
} //namespace hstefan
#endif