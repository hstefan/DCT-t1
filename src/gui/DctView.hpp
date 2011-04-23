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
		template <class T>
		class DctView : public scv::Canvas
		{
		public:
			typedef std::pair<unsigned int, unsigned int> vertex_type;
			static const unsigned int COMPONENT_SPACING_X = 10;
			static const unsigned int COMPONENT_SPACING_Y = 10;
			static const unsigned int CANVAS_HEIGHT = 200;
			static const unsigned int SQUARE_LENGTH = 3;

			DctView(const scv::Point& pi, const scv::Point& pf, 
				const std::vector<T>& coef = std::vector<T>());
			void render();
			void setCoefficients(const std::vector<T>& coef);
		protected:
			const short int width;
			std::vector<vertex_type> vertex_buffer;
		};

		template <class T>
		DctView<T>::DctView(const scv::Point& pi, const scv::Point& pf, 
			const std::vector<T>& coef)
			: scv::Canvas(pi, pf), vertex_buffer(), width(std::abs(pf.x - pi.x))
		{
			setCoefficients(coef);
		}

		template <class T>
		void DctView<T>::render()
		{
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

			glColor3f(1.0f, 0.f, 0.f);
			glBegin(GL_LINE_STRIP);
			for(std::vector<vertex_type>::const_iterator it = vertex_buffer.begin(); it != vertex_buffer.end(); ++it)
				glVertex2i((*it).first, (*it).second);
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(1.f, 0.f, 0.f);
			for(std::vector<vertex_type>::const_iterator it = vertex_buffer.begin(); it != vertex_buffer.end(); ++it)
			{	
				glVertex2i((*it).first - SQUARE_LENGTH, (*it).second + SQUARE_LENGTH);
				glVertex2i((*it).first + SQUARE_LENGTH, (*it).second + SQUARE_LENGTH);
				glVertex2i((*it).first + SQUARE_LENGTH, (*it).second - SQUARE_LENGTH);
				glVertex2i((*it).first - SQUARE_LENGTH, (*it).second - SQUARE_LENGTH);
			}
			glEnd();

			glLineWidth(.5f);
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(6, 0xAAAA); //linha tracejada
			glBegin(GL_LINE_STRIP);
			glColor3f(0.f, 0.f, 0.f);
			glVertex2i(0, CANVAS_HEIGHT/2);
			glVertex2i(width, CANVAS_HEIGHT/2);
			glEnd();

			glDisable(GL_LINE_STIPPLE);
			glDisable(GL_LINE_SMOOTH_HINT);
		}

		template <class T>
		void DctView<T>::setCoefficients(const std::vector<T>& coef)
		{
			vertex_buffer.clear();
			unsigned int x = 10;
			const unsigned int ratio = (width - COMPONENT_SPACING_X)/coef.size();
			T max = 0;
			for(std::vector<T>::const_iterator it = coef.begin(); it != coef.end(); ++it)
			{
				if (abs(*it) > max) 
					max = abs(*it);
			}
			for(std::vector<T>::const_iterator it = coef.begin(); it != coef.end(); ++it)
			{
				vertex_buffer.push_back( vertex_type(x, 
					(unsigned int)(-((CANVAS_HEIGHT/2.f)/(float)max) * (*it) + CANVAS_HEIGHT/2) ));
				x += ratio;
			}
		}
	}
}

#endif