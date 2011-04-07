#include "DCT.hpp"
#include <cmath>
#include <iostream>

#define HS_PI 3.1415926535897932 

namespace hstefan
{
	namespace dct
	{
		typedef DiscreteCosineTransform DCT;
		typedef DCT::output_type output_type;
		typedef DCT::signal_type signal_type;

		std::vector<output_type> DCT::fdct(const std::vector<signal_type>& sample)
		{
			double out = 0;
			std::vector<output_type> res;
			double cf = 1;
			for(unsigned int i = 0; i < sample.size(); ++i)
			{
				out = 0;
				if(i == 0)
					cf = (double)1/sqrt((double)2);
				else 
					cf = 1;
				for(unsigned int j = 0; j < sample.size(); ++j)
				{
					out += (double)sample[j] * cos((double)((2*j + 1)*i*HS_PI)/(2*sample.size()));		
				}
				out *= 0.5 * cf;
				res.push_back(out);
			}

			return res;
		}

		std::vector<signal_type> DCT::idct(const std::vector<output_type>& coef) 
		{
			return std::vector<signal_type>();
		}
	}

}