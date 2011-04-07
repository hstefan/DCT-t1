#include "DCT.hpp"
#include <cmath>
#include "../math/math.hpp"
#include <iostream>

#define HS_PI 3.14159265358979323846264338327950288419716939937510 

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
			for(unsigned int i = 0; i < sample.size(); ++i)
			{
				out = 0;
				for(unsigned int j = 0; j < sample.size(); ++j)
					out += (double)sample[j] * cos((double)((2*j + 1)*i*HS_PI)/(2*sample.size()));		
				out *= 0.5 * (i == 0? math::invSqrt(2) : 1);
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