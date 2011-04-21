
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
				virtual void onMouseClick( const scv::MouseEvent &evt );
			};
		private:
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
