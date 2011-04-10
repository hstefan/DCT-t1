#ifndef HSTEFAN_DCT_CANVAS_HPP
#define HSTEFAN_DCT_CANVAS_HPP

#include <SCV/Canvas.h>
#include "../dct/DCT.hpp"
#include <vector>
#include <SCV/Color4f.h>
#include <utility>

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
			typedef std::pair<unsigned int, unsigned int> vertex_type;
			static const unsigned int COMPONENT_SPACING_X = 10;
			static const unsigned int COMPONENT_SPACING_Y = 10;
			static const unsigned int CANVAS_HEIGHT = 360;
			static const unsigned int SQUARE_LENGTH = 3;


			DctCanvas(const unsigned int& container_width);
			
			/**
			 * Seta quais coeficentes serão desenhados.
			 */
			void setCoeficents(const std::vector<output_type>& coef);

			void render();
			inline unsigned int getCoefsNumber() const
			{
				return dct_coef.size();
			}

			inline std::vector<output_type>& getCoefs()
			{
				return dct_coef;
			}
		protected:
			/**
			 * Gera um buffer de vértices que serão desenhados futuramente na função render, já faz uma escala para desenhar de maneira mais visivel ao usario final.
			 * @param coefs coeficentes da DCT.
			 */
			void createBuffer(const std::vector<output_type>& coefs);
		private:
			std::vector<vertex_type> vertex_buffer;	
			std::vector<output_type> dct_coef;
			const unsigned int container_width;
			scv::Color4f bg_color;
			
		};
	}
}

#endif