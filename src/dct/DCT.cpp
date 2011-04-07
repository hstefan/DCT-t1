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

		output_type m_round(const output_type& in)
		{
			 return (output_type)(int(in + .5));
		}

		std::vector<output_type> DCT::fdct(const std::vector<signal_type>& sample)
		{
			double out = 0;
			std::vector<output_type> res;
			const unsigned int sz  = sample.size();
			for(unsigned int i = 0; i < sz; ++i)
			{
				out = 0;
				for(unsigned int j = 0; j < sz; ++j)
					out += (output_type)sample[j] * cos((double)((2*j + 1)*i*HS_PI)/(2*sz));		
				out *= 0.5 * (i == 0? math::invSqrt(2) : 1);
				res.push_back(out);
			}
			return res;
		}

		std::vector<signal_type> DCT::idct(const std::vector<output_type>& coef) 
		{
			double out = 0;
			std::vector<signal_type> res;
			const unsigned int sz  = coef.size();
			for(unsigned int i = 0; i < sz; ++i) 
			{
				out = 0;
				for(unsigned int j = 0; j < sz; ++j) 
					out += coef[j] * (j == 0 ? math::invSqrt(2) : 1) *
						cos(((2*i + 1)*j*HS_PI)/(2*sz));
				out *= .5;
				out = floor(out + .5); //arredonda o numero
				res.push_back((signal_type)out);
			}
			std::cout << std::endl;
			return res;
		}
	}

}