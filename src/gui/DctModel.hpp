#ifndef HSTEFAN_DCT_MODEL_HPP
#define HSTEFAN_DCT_MODEL_HPP

#include <vector>
#include "../dct/DCT.hpp"

namespace hstefan
{
	namespace gui
	{
		class DctModel
		{
		public:
			typedef dct::DiscreteCosineTransform::signal_type signal_type;
			typedef dct::DiscreteCosineTransform::signal_type output_type;

			DctModel(const std::vector<signal_type>& signal);

		private:
			std::vector<signal_type> signal;
			std::vector<output_type> output;
		};
	}
}

#endif