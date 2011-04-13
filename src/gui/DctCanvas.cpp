#include "DctCanvas.hpp"
#include <cmath>

namespace hstefan
{
	namespace gui
	{
		DctCanvas::DctCanvas(const unsigned int& window_width)
			: container_width(window_width), vertex_buffer(), 
			scv::Canvas(scv::Point(COMPONENT_SPACING_X, COMPONENT_SPACING_Y), 
			scv::Point(window_width - COMPONENT_SPACING_X, CANVAS_HEIGHT - COMPONENT_SPACING_Y)),
			bg_color(1.0f, 1.0f, 1.0f, 0.1f)
		{}

		void DctCanvas::setCoeficents(const std::vector<output_type>& coef)
		{
			dct_coef = coef; 
			createBuffer(coef);
		}

		void DctCanvas::render()
		{
			glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
			glDisable(GL_TEXTURE);
			glClear(GL_COLOR_BUFFER_BIT);
			
			glLineWidth(.5f);
			glBegin(GL_LINE_STRIP);
				glColor3f(0.f, 0.f, 0.f);
				glVertex2i(0, CANVAS_HEIGHT/2);
				glVertex2i(container_width, CANVAS_HEIGHT/2);
			glEnd();

			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			
			glLineWidth(1.5f);
			glBegin(GL_LINE_STRIP);
				glColor3f(1.f, 0.f, 0.3f);
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

			glDisable(GL_LINE_SMOOTH_HINT);
		}

		void DctCanvas::createBuffer(const std::vector<output_type>& coefs)
		{
			vertex_buffer.clear();
			unsigned int x = 10;
			const unsigned int ratio = (container_width - COMPONENT_SPACING_X)/coefs.size();
			output_type max = 0;
			for(std::vector<output_type>::const_iterator it = coefs.begin(); it != coefs.end(); ++it)
			{
				if (abs(*it) > max) 
					max = abs(*it);
			}
			for(std::vector<output_type>::const_iterator it = coefs.begin(); it != coefs.end(); ++it)
			{
				vertex_buffer.push_back( vertex_type(x, 
					(unsigned int)(-((CANVAS_HEIGHT/2.f)/(float)max) * (*it) + CANVAS_HEIGHT/2) ));
				x += ratio;
			}
		}
	}
}