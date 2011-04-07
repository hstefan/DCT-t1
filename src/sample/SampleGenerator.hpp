#ifndef HSTEFAN_SIGNAL_GENERATOR_HPP
#define HSTEFAN_SIGNAL_GENERATOR_HPP

#include <vector>

namespace hstefan
{
	namespace sample
	{
		/**
		 * Classe usada para gerar amostras de sinal. 
		 */
		class SampleGenerator 
		{
		public:
			typedef unsigned char signal_type;

			/**
			 * Gera a amostra propriamente dita.
			 * @param n Tamanho da amostra.
			 */
			virtual void generateSample(unsigned int n) = 0;
			
			/**
			 * Retorna a amostra gerada.
			 * @return std::vector com a amostra.
			 */
			inline std::vector<signal_type>& getSample();
			inline const std::vector<signal_type>& getSample() const;
		protected:
			/**
			 * Vetor usado para armazenar a amostra.
			 */
			std::vector<signal_type> signal;
		};

		std::vector<SampleGenerator::signal_type>& SampleGenerator::getSample() 
		{
			return signal;
		}

		const std::vector<SampleGenerator::signal_type>& SampleGenerator::getSample() const
		{
			return signal;
		}
	} //namespace sample
} //namespace hstefan

#endif