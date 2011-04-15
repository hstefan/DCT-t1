#include "DctView.hpp"
#include <cmath>

using namespace hstefan::gui;

GLuint positionBufferObject;

DctView::DctView(const scv::Point& pi, const scv::Point& pf, 
	const std::vector<output_type>& coef)
	: scv::Canvas(pi, pf), vertex_buff(0), buff_size(0), id(0), width(pf.x - pi.x),
	buff_len(0)
{
	setCoefficients(coef);
}

void DctView::render()
{
	glGenBuffers(1, &positionBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, buff_size, vertex_buff, GL_STATIC_DRAW);
	glVertexPointer(2, GL_SHORT, 0, 0);
	glDrawArrays(GL_LINE_STRIP, 0, buff_len/2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void DctView::setCoefficients(const std::vector<output_type>& coef)
{
	if(vertex_buff != 0)
		delete[] vertex_buff;
	short int x = 10;
	const short int ratio = (width - COMPONENT_SPACING_X)/coef.size();
	output_type max = 0;
	for(std::vector<output_type>::const_iterator it = coef.begin(); it != coef.end(); ++it)
	{
		if (abs(*it) > max) 
			max = abs(*it);
	}
	
	std::vector<output_type>::const_iterator it = coef.begin();
	unsigned int i = 0;

	for(; it != coef.end(); ++it, ++i)
	{
		vertex_buff[i]= x;
		vertex_buff[++i] = (unsigned int)(-((CANVAS_HEIGHT/2.f)/(float)max) * (*it) + CANVAS_HEIGHT/2) );
		x += ratio;
	}

	buff_len = coef.size();
	buff_size = buff_len * sizeof(short int) * 2;
}