#ifndef HSTEFAN_DCT_VIEW_HPP
#define HSTEFAN_DCT_VIEW_HPP

#include <SCV/Canvas.h>
#include <vector>
#include <utility>
#include "../dct/DCT.hpp"

namespace hstefan
{
	namespace gui
	{
		class DctView : public scv::Canvas
		{
		public:
			typedef dct::DiscreteCosineTransform::output_type output_type;
			static const unsigned int COMPONENT_SPACING_X = 10;
			static const unsigned int COMPONENT_SPACING_Y = 10;
			static const unsigned int CANVAS_HEIGHT = 360;
			static const unsigned int SQUARE_LENGTH = 3;

			DctView(const scv::Point& pi, const scv::Point& pf, 
				const std::vector<output_type>& coef = std::vector<output_type>());
			void render();
			void setCoefficients(const std::vector<output_type>& coef);
		protected:
			const short int width;
			short int* vertex_buff;
			unsigned int buff_size;
			unsigned int buff_len;
			GLuint id;
		};
	}
}

#endif