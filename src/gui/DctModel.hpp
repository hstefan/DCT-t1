#ifndef HSTEFAN_DCT_MODEL_HPP
#define HSTEFAN_DCT_MODEL_HPP

#include <vector>
#include "../dct/DCT.hpp"
#include "../util/Listener.hpp"

namespace hstefan
{
	namespace gui
	{
		class DctModel
		{
		public:
			typedef dct::DiscreteCosineTransform::signal_type signal_type;
			typedef dct::DiscreteCosineTransform::output_type output_type;

			DctModel(const std::vector<signal_type>& signal);

			const std::vector<signal_type>& signal() const;
			const std::vector<output_type>& coefficients() const;

			void setSignal(const std::vector<signal_type>& signal);
		private:
			void applyDct();
		private:
			std::vector<signal_type> m_signal;
			std::vector<output_type> m_output;
		};
	}
}

#endif