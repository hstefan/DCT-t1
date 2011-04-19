#include "CoefTable.hpp"
#include <iostream>
#include <deque>
#include <SCV/Kernel.h>
#include <SCV/KeyEvent.h>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <SCV/TextBox.h>

namespace hstefan
{
	namespace gui
	{
		CoefTable::CoefTable(const scv::Point& pos, unsigned int width, const std::vector<signal_type>& signal_row,
			const std::vector<output_type>& output_row)
			: scv::Table(pos, 2, signal_row.size(), 1, width/signal_row.size()), coef_vec(output_row), signal_vec(signal_row),
			uinteger_filter(), double_filter()
		{
			std::ostringstream stream;

			for(unsigned int i = 0; i < signal_row.size(); i++)
			{
				stream << (unsigned int)signal_row[i];
				setString(0, i, stream.str());
				stream.seekp(0);
				stream.clear();
			}

			for(unsigned int i = 0; i < output_row.size(); i++)
			{
				stream << output_row[i];
				setString(1, i, stream.str());
				stream.seekp(0);
				stream.clear();
			}

			uinteger_filter.denyAll();
			uinteger_filter.allowNumbers();
	
			std::deque<std::deque<scv::TextBox*>>::iterator table_begin_iter = _table.begin();
			std::deque<std::deque<scv::TextBox*>>::iterator table_end_iter = _table.end();
			
			std::deque<scv::TextBox*>::iterator row_iter, row_end_it;

			for(row_end_it = (*table_begin_iter).begin(), row_iter = (*table_begin_iter).end(); row_end_it != row_iter; ++row_end_it) //adciona filtro que permite que apenas numeros sejam inseridos
				(*row_end_it)->setFilter(uinteger_filter);

			double_filter.denyAll();
			double_filter.allowNumbers();
			double_filter.allowThese("-."); 
			
			++table_begin_iter;
			for(row_end_it = (*table_begin_iter).begin(), row_iter = (*table_begin_iter).end(); row_end_it != row_iter; ++row_end_it) //adciona filtro que permite o sinal negativo e pontos
				(*row_end_it)->setFilter(double_filter);
		}

		void CoefTable::onKeyUp( const scv::KeyEvent &evt )
		{
			scv::Table::onKeyUp(evt);

			if(uinteger_filter.checkFilter(evt.getKeyCode()) || double_filter.checkFilter(evt.getKeyCode()))
			{
				unsigned int row_updated = 0;
				int col_number = getNumberOfColumns();
				std::ostringstream stream;

				for(int i = 0; i < col_number; ++i)
				{
					stream << (unsigned int)signal_vec[i];
					if(getString(0, i) != stream.str())
					{
						onSampleRowChange(evt);
						break;
					}
					stream.seekp(0);
					stream.clear();
				}

				stream.seekp(0);
				stream.clear();
				
				for(int i = 0; i < col_number; ++i)
				{
					stream << coef_vec[i];
					if(getString(1, i) != stream.str())
					{
						onCoefficientsRowChange(evt);
						break;
					}
					stream.seekp(0);
					stream.clear();
				}
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

			Table::processMouse(evt);
		}

		void CoefTable::onSampleRowChange(const scv::KeyEvent& evt)
		{
			std::cout << "alteracao no sinal" << std::endl;	
		}

		void CoefTable::onCoefficientsRowChange(const scv::KeyEvent& evt)
		{
			std::cout << "alteracao no coeficiente" << std::endl;
		}

	} //namespace gui
} //namespace hstefan