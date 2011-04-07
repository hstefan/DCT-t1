#include "DCT.hpp"
#include <cmath>
#include <iostream>

#define HS_PI 3,1415926535897932 

namespace hstefan
{
	namespace dct
	{
		typedef DiscreteCosineTransform DCT;
		typedef DCT::output_type output_type;
		typedef DCT::signal_type signal_type;

		std::vector<output_type> DCT::fdct(const std::vector<signal_type>& sample)
		{
			std::vector<signal_type>::const_iterator end = sample.end();
			unsigned int i = 0;
			output_type out = 0;
			std::vector<output_type> ret;
			
			for(std::vector<signal_type>::const_iterator it = sample.begin(); it != end; ++it)
			{
				out = 0;
				for(unsigned int j = i; j < sample.size(); ++j)
				{
					out += (*it) * cos((double)((2*j + 1)*i*HS_PI/(2 * sample.size())));
				}
				out *= 0.5 * (i == 0 ? (double)1/sqrt((double)2) : 1);
				std::cout << out << std::endl;
				ret.push_back(out);
				++i;
			}
			return ret;
		}

		std::vector<signal_type> DCT::idct(const std::vector<output_type>& coef) 
		{
			return std::vector<signal_type>();
		}
	}

}