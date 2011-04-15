#include "CoefTable.hpp"
#include <iostream>
#include <deque>
#include <SCV/Kernel.h>
#include <SCV/KeyEvent.h>
#include <cctype>
#include <cstring>

namespace hstefan
{
	namespace gui
	{
		CoefTable::CoefTable(const scv::Point& pos, unsigned int width, const std::vector<signal_type>& signal_row,
			const std::vector<output_type>& output_row)
			: scv::Table(pos, 2, signal_row.size(), 1, 100), coef_vec(output_row), signal_vec(signal_row), 
			text_filter(new scv::TextFilter())
		{
			std::string out = "";
			for(int i = 0; i < signal_row.size(); i++)
			{
				coef_stream << signal_row[i];
				coef_stream >> out;
				setString(0, i, out);
				coef_stream.seekg(0);
				coef_stream.seekp(0);
				coef_stream.clear();
			}

			for(int i = 0; i < output_row.size(); i++)
			{
				coef_stream << output_row[i];
				coef_stream >> out;
				setString(1, i, out);
				coef_stream.seekg(0);
				coef_stream.seekp(0);
				coef_stream.clear();
			}

			text_filter->denyAll();
			text_filter->allowNumbers();

			for(std::deque<std::deque<scv::TextBox*>>::iterator it =_table.begin(); it != _table.end(); ++it)
			{
				for(std::deque<scv::TextBox*>::iterator ij = (*it).begin(); ij != (*it).end(); ++ij)
				{
					(*ij)->setFilter(*text_filter);
				}
			}
		}

		void CoefTable::onKeyUp( const scv::KeyEvent &evt )
		{
			if(text_filter->checkFilter(evt.getKeyCode()))
				notifyObservers();
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

			Table::processMouse(evt);
		}
	} //namespace gui
} //namespace hstefan