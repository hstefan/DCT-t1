#include "CoefTable.hpp"
#include <iostream>
#include <deque>

namespace hstefan
{
	namespace gui
	{
		CoefTable::CoefTable(unsigned int n, const std::vector<output_type>& dct_out, 
			const scv::Point& pos, unsigned int width)
			: Table(pos, 1, n, 1, width/n), coef_vec(dct_out), coef_stream()
		{
			initTable();
		}

		void CoefTable::initTable()
		{
			unsigned int cel = 0;
			for(std::vector<output_type>::const_iterator it = coef_vec.begin(); it != coef_vec.end(); ++it)
			{
				coef_stream << (*it);
				setString(0, cel, coef_stream.str());
				coef_stream.clear();
				coef_stream.seekg(0);
				coef_stream.seekp(0);
				++cel;
			}
		}

		/**
		* Retorna os valores da tabela ao estado inicial (necessário, pois os campos não devem ser editáveis).
		*/
		void CoefTable::onKeyUp( const scv::KeyEvent &evt )
		{
			/*std::cout << "key up" << std::endl;*/
			initTable();
		}

	} //namespace gui
} //namespace hstefan