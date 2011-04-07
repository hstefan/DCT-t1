#ifndef HSTEFAN_DCT_HPP
#define HSTEFAN_DCT_HPP

#include <vector>

namespace hstefan
{
	namespace dct
	{
		/*
		 * Classe usada para aplicar a DCT e IDCT em uma dada entrada.
		 */
		class DiscreteCosineTransform
		{
		public:
			typedef unsigned char signal_type;
			typedef double output_type;

			static std::vector<output_type> fdct(const std::vector<signal_type>& sample);
			static std::vector<signal_type> idct(const std::vector<output_type>& coef);
		};
	}
}

#endif