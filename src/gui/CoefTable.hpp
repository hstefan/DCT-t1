#ifndef HSTEFAN_COEF_TABLE_HPP
#define HSTEFAN_COEF_TABLE_HPP

#include <SCV/Table.h>
#include "../dct/DCT.hpp"
#include <sstream>
#include <stack>
#include "SCV/Point.h"
#include <SCV/TextField.h>
#include "../util/Observable.hpp"

namespace hstefan
{
	namespace gui
	{
		/**
		* Tabela para visualização e alteração dos coeficientes de saida.
		*/
		class CoefTable : public scv::Table, public util::Observable
		{
		public:
			typedef dct::DiscreteCosineTransform::output_type output_type;
			typedef dct::DiscreteCosineTransform::signal_type signal_type;

			/**
			* @param pos Posição da Table na janela.
			* @param width Largura da janela.
			* @param signal_row Coeficientes de entrada (linha sample).
			* @param output_row Coeficientes de saidada DCT (linha DCT).
			*/
			CoefTable::CoefTable(const scv::Point& pos, unsigned int width, const std::vector<signal_type>& signal_row,
				const std::vector<output_type>& output_row);

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

			inline const std::vector<output_type>& getCoefficients() const
			{
				return coef_vec;
			}

			inline const std::vector<signal_type>& getSignal() const
			{
				return signal_vec;
			}
			/**
			 * Realiza ações necessárias para o bom funcionamente do programa quando a linha de amostras for alterada.
			 */
			void onSampleRowChange(const scv::KeyEvent& evt);

			/**
			 * Realiza ações necessárias para o bom funcionamente do programa quando a linha de coeficientes da DCT for alterada.
			 */
			void onCoefficientsRowChange(const scv::KeyEvent& evt);
		private:
			void initTable();

			std::vector<output_type> coef_vec;
			std::vector<signal_type> signal_vec; 
			std::stringstream coef_stream;
			scv::TextFilter* text_filter;
		};
	}//namespace gui
}//namespace hstefan

#endif