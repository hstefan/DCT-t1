
#ifndef HSTEFAN_SAMPLE_GENERATION_PANEL_HPP
#define HSTEFAN_SAMPLE_GENERATION_PANEL_HPP

#include <SCV/Panel.h>
#include <SCV/Button.h>
#include <SCV/ComboBox.h>
#include <SCV/Label.h>
#include "CoefTable.hpp"
#include "../sample/LinearGen.hpp"
#include "../sample/RandomGen.hpp"
#include <vector>

namespace hstefan
{
	namespace gui
	{
		class SampleGenerationPanel : public scv::Panel
		{
		public:
			SampleGenerationPanel(scv::Point pi, unsigned int width, CoefTable* table);

			static const unsigned int PANEL_HEIGHT = 85;
			static const unsigned int W_SPACING = 5;
			static const unsigned int H_SPACING = 5;
			static const unsigned int COMBO_WIDTH = 120;
		protected:
			class SampleButton : public scv::Button
			{ 
			public:
				SampleButton(SampleGenerationPanel* pan, unsigned int y, unsigned int w)
					: scv::Button(scv::Point(W_SPACING, y), w, "Gerar Amostra"), panel(pan)
				{
				}
				virtual void onMouseClick( const scv::MouseEvent &evt )
				{
					panel->generateSample();
				}
			private:
				SampleGenerationPanel* panel;
			};

			void generateSample()
			{
				if(sample_box.getIndex() < 0 || len_box.getIndex() < 0)
					return;

				std::string sample_type = sample_box.getValue();
				std::string sample_len = len_box.getValue();

				if(sample_type != "" && sample_len != "")
				{
					unsigned int sz = atoi(sample_len.c_str());
					sample::SampleGenerator* sample_gen = 0;
					if(sample_type == "Aleatoria")
						sample_gen = new sample::RandomGen();
					else if (sample_type == "Linear")
						sample_gen = new sample::LinearGen();
					if(sample_gen != 0)
					{
						sample_gen->generateSample(sz);
						std::vector<sample::SampleGenerator::signal_type> signal(sample_gen->getSample());
						table_ptr->setSampleRow(signal);
						table_ptr->onSampleRowChange();
						delete sample_gen;
					}
				}
			}
		private:
			friend class SampleButton;

			scv::Label len_label;
			scv::Label type_label;
			scv::ComboBox sample_box;
			scv::ComboBox len_box;
			CoefTable* table_ptr;
			SampleButton sample_button;
		};
	
	}
}

#endif
