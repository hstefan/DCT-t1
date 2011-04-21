#ifndef HSTEFAN_INTERFACE_HPP
#define HSTEFAN_INTERFACE_HPP

#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include "CoefTable.hpp"
#include "DctController.hpp"
#include "SampleGenerationPanel.hpp"

namespace hstefan
{
	namespace gui
	{
		class Interface
		{
		public:
			Interface();

			static const unsigned int W_WIDTH = 640;
			static const unsigned int W_HEIGHT = 480;

		private:
			scv::Kernel* kernel;
			scv::ColorScheme* color_scheme;
			DctController<CoefTable>* controller;
			DctView* view;
			DctModel* model;
			CoefTable* coef_tab;
			SampleGenerationPanel* sample_panel;
		};
	}
}

#endif