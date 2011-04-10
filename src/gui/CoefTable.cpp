#include "CoefTable.hpp"
#include <iostream>
#include <deque>
#include <SCV/Kernel.h>
#include <SCV/KeyEvent.h>

namespace hstefan
{
	namespace gui
	{
		CoefTable::CoefTable(DctCanvas* canvas, const scv::Point& pos, unsigned int width)
			: Table(pos, 1, canvas->getCoefsNumber(), 1, width/canvas->getCoefsNumber()), 
			coef_vec(&canvas->getCoefs()), canvas(canvas)
		{
			initTable();
		}

		void CoefTable::initTable()
		{
			unsigned int cel = 0;
			for(std::vector<output_type>::const_iterator it = coef_vec->begin(); it != coef_vec->end(); ++it)
			{
				coef_stream << (*it);
				setString(0, cel, coef_stream.str());
				coef_stream.clear();
				coef_stream.seekg(0);
				coef_stream.seekp(0);
				++cel;
			}
		}

		void CoefTable::onKeyUp( const scv::KeyEvent &evt )
		{
			output_type coef = 0;
			for(unsigned int i = 0; i < this->getNumberOfColumns(); ++i)
			{
				coef_stream << getString(0, i);
				coef_stream >> coef;
				(*coef_vec)[i] = coef;
				coef_stream.clear();
				coef_stream.seekg(0);
				coef_stream.seekp(0);
			}
		}

		void CoefTable::processKey( const scv::KeyEvent &evt )
		{
			if(evt.getState() == evt.up)
				onKeyUp(evt);
			else if(evt.getState() == evt.down)
				onKeyPressed(evt);

			Table::processKey(evt);
		}

		void CoefTable::processMouse(const scv::MouseEvent &evt)
		{
			if(evt.getState() == evt.click)
				onMouseClick(evt);
			else if(evt.getState() == evt.hold)
				onMouseHold(evt);
			else if(evt.getState() == evt.up)
				onMouseUp(evt);
		}
	} //namespace gui
} //namespace hstefan