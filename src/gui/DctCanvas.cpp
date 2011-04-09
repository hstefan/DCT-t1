#include "DctCanvas.hpp"
#include <cmath>
#include <iostream>

namespace hstefan
{
	namespace gui
	{
		DctCanvas::DctCanvas(const unsigned int& window_width)
			: container_width(window_width), vertex_buffer(), 
			scv::Canvas(scv::Point(COMPONENT_SPACING_X, COMPONENT_SPACING_Y), 
			scv::Point(window_width - COMPONENT_SPACING_X, CANVAS_HEIGHT - COMPONENT_SPACING_Y)),
			bg_color(1.0,1.0,1.0, 0.1)
		{}

		void DctCanvas::setCoeficents(const std::vector<output_type>& coef)
		{
			createBuffer(coef);
		}

		void DctCanvas::render()
		{
			glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_LINE_STRIP);
				glColor3f(1.f, 0.f, 0.093);
				for(std::vector<vertex_type>::const_iterator it = vertex_buffer.begin(); it != vertex_buffer.end(); ++it)
					glVertex2i((*it).first, (*it).second);
			glEnd();

			glBegin(GL_QUADS);
				for(std::vector<vertex_type>::const_iterator it = vertex_buffer.begin(); it != vertex_buffer.end(); ++it)
				{	
					glVertex2i((*it).first - SQUARE_LENGTH, (*it).second + SQUARE_LENGTH);
					glVertex2i((*it).first + SQUARE_LENGTH, (*it).second + SQUARE_LENGTH);
					glVertex2i((*it).first + SQUARE_LENGTH, (*it).second - SQUARE_LENGTH);
					glVertex2i((*it).first - SQUARE_LENGTH, (*it).second - SQUARE_LENGTH);
				}
			glEnd();
		}

		void DctCanvas::createBuffer(const std::vector<output_type>& coefs)
		{
			unsigned int x = 10;
			const unsigned int ratio = (container_width - COMPONENT_SPACING_X)/coefs.size();
			unsigned int max = 0;
			for(std::vector<output_type>::const_iterator it = coefs.begin(); it != coefs.end(); ++it)
			{
				if (abs(*it) > max) 
					max = abs(*it);
			}
			for(std::vector<output_type>::const_iterator it = coefs.begin(); it != coefs.end(); ++it)
			{
				//glVertex2i(x, ((CANVAS_HEIGHT/2.f)/(float)max) *(*it) + CANVAS_HEIGHT/2);
				vertex_buffer.push_back( vertex_type(x, 
					((CANVAS_HEIGHT/2.f)/(float)max) *(*it) + CANVAS_HEIGHT/2) );
				x += ratio;
			}
		}
	}
}