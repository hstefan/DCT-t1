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
				setString(SAMPLE_ROW_NUMBER, i, stream.str());
				stream.str("");
				stream.clear();
			}

			for(unsigned int i = 0; i < output_row.size(); i++)
			{
				stream << output_row[i];
				setString(COEF_ROW_NUMBER, i, stream.str());
				stream.str("");
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
						onSampleRowChange(evt, (unsigned int)i);
						break;
					}
					stream.str("");
					stream.clear();
				}

				stream.seekp(0);
				stream.clear();
				
				for(int i = 0; i < col_number; ++i)
				{
					stream << coef_vec[i];
					if(getString(1, i) != stream.str())
					{
						onCoefficientsRowChange(evt, (unsigned int)i);
						break;
					}
					stream.str("");
					stream.clear();
				}
			}
		}

		void CoefTable::processKey( const scv::KeyEvent &evt )
		{
			Table::processKey(evt);

			if(evt.getState() == evt.up)
				onKeyUp(evt);
			else if(evt.getState() == evt.down)
				onKeyPressed(evt);
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

		void CoefTable::onSampleRowChange(const scv::KeyEvent& evt, unsigned int cel_number)
		{
			normalizeSampleRow();
			signal_vec.clear();
			for(int i = 0; i < getNumberOfColumns(); ++i)
				signal_vec.push_back(atoi(getString(SAMPLE_ROW_NUMBER, i).c_str()));
			notifyObservers();
		}

		void CoefTable::onCoefficientsRowChange(const scv::KeyEvent& evt,  unsigned int cel_number)
		{
			if(evt.getKeyCode() == '.' || evt.getKeyCode() == '-')
			{
				std::string str_cel = getString(COEF_ROW_NUMBER, cel_number);
				if(std::count(str_cel.begin(), str_cel.end(), evt.getKeyCode()) > 1)
				{
					std::ostringstream stream;
					stream << coef_vec[cel_number];
					setString(COEF_ROW_NUMBER, cel_number, stream.str());
				}
			}
			coef_vec[cel_number] = atoi(getString(COEF_ROW_NUMBER, cel_number).c_str());
			notifyObservers();
		}

		void CoefTable::normalizeSampleRow()
		{
			int tmp = 0;
			for(int i = 0; i < getNumberOfColumns(); ++i)
			{
				tmp = atoi(getString(SAMPLE_ROW_NUMBER, i).c_str());
				if(tmp > 255)
					setString(SAMPLE_ROW_NUMBER, i, "255");
			}
		}

		void CoefTable::setCoefficientstRow(const std::vector<output_type>& dct_row)
		{
			coef_vec.resize(dct_row.size());
			std::ostringstream stream;
			for(int i = 0; i < getNumberOfColumns(); ++i)
			{
				coef_vec[i] = dct_row[i];
				stream << dct_row[i];
				setString(COEF_ROW_NUMBER, i, stream.str());
				stream.str(""); 
				stream.clear();
			}
		}

		void CoefTable::setSampleRow(const std::vector<signal_type>& signal_row)
		{
			signal_vec.resize(signal_row.size());
			std::ostringstream stream;
			for(int i = 0; i < getNumberOfColumns(); ++i)
			{
				signal_vec[i] = signal_row[i];
				stream << (unsigned int)signal_vec[i];
				setString(SAMPLE_ROW_NUMBER, i, stream.str());
				stream.str("");
				stream.clear();
			}
		}

		void CoefTable::onSampleRowChange()
		{
			notifyObservers();
		}

		void CoefTable::resizeTable()
		{
			std::deque<std::deque<scv::TextBox*>>::iterator rows_iter = _table.begin();
			std::deque<std::deque<scv::TextBox*>>::iterator rows_end_iter = _table.end();

			std::deque<scv::TextBox*>::reverse_iterator rev_iter_column;
			std::deque<scv::TextBox*>::reverse_iterator rev_iter_begin;

			int diff = getNumberOfColumns() - signal_vec.size();
			int left = diff;
			if(diff < 0)
			{
				for(; rows_iter != rows_end_iter; ++rows_iter)
				{
					left = std::abs(diff);
					for(rev_iter_column = (*rows_iter).rend(), rev_iter_begin = (*rows_iter).rbegin(); 
						rev_iter_column != rev_iter_begin; ++rev_iter_column)
					{
						(*rows_iter).erase(rev_iter_column.base());	
						left--;
					}
				}
			}

			else if(diff > 0)
			{
				while(left-- >= 0)
				{

				}
			}
		}
	} //namespace gui
} //namespace hstefan