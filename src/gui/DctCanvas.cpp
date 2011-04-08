#include "DctCanvas.hpp"

namespace hstefan
{
	namespace gui
	{
		DctCanvas::DctCanvas(const unsigned int& window_width)
			: container_width(window_width), coefs(), 
			scv::Canvas(scv::Point(COMPONENT_SPACING_X, COMPONENT_SPACING_Y), 
			scv::Point(window_width, CANVAS_HEIGHT)),
			bg_color(1.0,1.0,1.0, 0.5)
		{
		}

		void DctCanvas::setCoeficents(const std::vector<output_type>& coef)
		{
			coefs = coef;
		}

		void DctCanvas::render()
		{
			glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_LINE_STRIP);
				glColor3f(0.f, 0.f, 1.f);
				unsigned int x = COMPONENT_SPACING_X;
				const unsigned int ratio = (container_width - 2*COMPONENT_SPACING_X)/coefs.size();
				bool sec = false;

				for(std::vector<output_type>::const_iterator it = coefs.begin(); it != coefs.end(); ++it)
				{
					glVertex2i(x, (*it + CANVAS_HEIGHT/2) + COMPONENT_SPACING_Y);
					x += ratio;
				}
			glEnd();
		}
	}
}