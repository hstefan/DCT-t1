#ifndef HSTEFAN_SIGNAL_GENERATOR_HPP
#define HSTEFAN_SIGNAL_GENERATOR_HPP

#include <vector>

namespace hstefan
{
	namespace sample
	{
		class SampleGenerator 
		{
		public:
			typedef double signal_type;
			virtual void generateSample(unsigned int n) = 0;
			inline std::vector<signal_type>& getSample();
			inline const std::vector<signal_type>& getSample() const;
		protected:
			std::vector<signal_type> signal;
		};

		std::vector<SampleGenerator::signal_type>& SampleGenerator::getSample() 
		{
			return signal;
		}

		const std::vector<SampleGenerator::signal_type>& SampleGenerator::getSample() const
		{
			return signal;
		}
	} //namespace sample
} //namespace hstefan

#endif