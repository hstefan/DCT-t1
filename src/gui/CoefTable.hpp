#ifndef HSTEFAN_COEF_TABLE_HPP
#define HSTEFAN_COEF_TABLE_HPP

#include <SCV/Table.h>
#include "../dct/DCT.hpp"
#include <sstream>
#include <stack>
#include "DctCanvas.hpp"

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
			CoefTable(DctCanvas* canvas, const scv::Point& pos, unsigned int width);

			/**
			* Atualiza os coeficientes da tabela.
			* @param coefs Novos coeficientes.
			*/
			inline void updateCoefs(std::vector<output_type>* coefs)
			{
				coef_vec = coefs;
				initTable(); //reseta a tabela
			}
			/**
			 * Atualiza os valores no canvas.
			 */
			virtual void onKeyUp(const scv::KeyEvent &evt );

			/**
			 * Overload da função processKey, apenas corrige o bug das callbacks de teclado e chama a função original.
			 */
			virtual void processKey(const scv::KeyEvent &evt);
			
			/**
			 * Faz com que as callbacks de mouse sejam chamadas e chama a função original.
			 */
			virtual void processMouse(const scv::MouseEvent &evt);

		private:
			void initTable();

			std::vector<output_type>* coef_vec;
			std::stringstream coef_stream;
			DctCanvas* canvas;

		};
	}//namespace gui
}//namespace hstefan

#endif