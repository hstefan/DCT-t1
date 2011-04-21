
#ifndef HSTEFAN_SAMPLE_GENERATION_PANEL_HPP
#define HSTEFAN_SAMPLE_GENERATION_PANEL_HPP

#include <SCV/Panel.h>
#include <SCV/Button.h>
#include <SCV/ComboBox.h>
#include <SCV/Label.h>
#include "CoefTable.hpp"

namespace hstefan
{
	namespace gui
	{
		class SampleGenerationPanel : public scv::Panel
		{
		public:
			SampleGenerationPanel(scv::Point pi, unsigned int width, CoefTable* table);

			static const unsigned int PANEL_HEIGHT = 50;
			static const unsigned int W_SPACING = 5;
			static const unsigned int H_SPACING = 5;
			static const unsigned int COMBO_WIDTH = 40;
		protected:
			class SampleButton : public scv::Button
			{ 
			public:
				SampleButton(SampleGenerationPanel* pan)
					: scv::Button(scv::Point(W_SPACING, pan->len_box.getHeight()*3), pan->getWidth() - 2*H_SPACING, "Gerar Amostra"), panel(pan)
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
