#ifndef HSTEFAN_COEF_TABLE_HPP
#define HSTEFAN_COEF_TABLE_HPP

#include <SCV/Table.h>
#include "../dct/DCT.hpp"
#include <sstream>
#include <stack>

namespace hstefan
{
	namespace gui
	{
		/**
		* Tabela para visualização e alteração dos coeficientes de saida.
		*/
		class CoefTable : public scv::Table
		{
		public:
			typedef dct::DiscreteCosineTransform::output_type output_type;

			/**
			* @param n Numero de celulas da tabela.
			* @param dct_out Coeficientes de saidada DCT.
			* @param pos Posição da Table na janela.
			* @param width Largura da janela.
			*/
			CoefTable(unsigned int n, const std::vector<output_type>& dct_out, const scv::Point& pos, 
				unsigned int width);

			/**
			* Atualiza os coeficientes da tabela.
			* @param coefs Novos coeficientes.
			*/
			inline void updateCoefs(const std::vector<output_type>& coefs)
			{
				coef_vec = coefs;
				initTable(); //reseta a tabela
			}
			
			virtual void onKeyUp(const scv::KeyEvent &evt );
		protected:
			void undo();
			void storeCels();
		private:
			void initTable();

			std::vector<output_type> coef_vec;
			std::stringstream coef_stream;

		};
	}//namespace gui
}//namespace hstefan

#endif