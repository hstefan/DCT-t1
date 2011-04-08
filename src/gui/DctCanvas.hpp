#ifndef HSTEFAN_DCT_CANVAS_HPP
#define HSTEFAN_DCT_CANVAS_HPP

#include <SCV/Canvas.h>
#include "../dct/DCT.hpp"
#include <vector>
#include <SCV/Color4f.h>

namespace hstefan
{
	namespace gui
	{
		/**
		 * Canvas para desenhar o grafico do resultado da DCT aplicada em uma determinada amostra.
		 */
		class DctCanvas : public scv::Canvas
		{
		public:
			typedef dct::DiscreteCosineTransform::output_type output_type;

			static const unsigned int COMPONENT_SPACING_X = 10;
			static const unsigned int COMPONENT_SPACING_Y = 10;
			static const unsigned int CANVAS_HEIGHT = 360;

			DctCanvas(const unsigned int& container_width);
			
			/**
			 * Seta quais coeficentes serão desenhados.
			 */
			void setCoeficents(const std::vector<output_type>& coef);
			void render();
		private:
			std::vector<output_type> coefs;	
			const unsigned int container_width;
			scv::Color4f bg_color;
			
		};
	}
}

#endif