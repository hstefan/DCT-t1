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

         static const unsigned int W_WIDTH = 650;
         static const unsigned int W_HEIGHT = 480;

         typedef dct::DiscreteCosineTransform::signal_type signal_type;
         typedef dct::DiscreteCosineTransform::output_type output_type;

      private:
         scv::Kernel* kernel;
         scv::ColorScheme* color_scheme;
         DctController<CoefTable>* controller;
         DctView<output_type>* view;
         DctView<signal_type>* sig_view;
         DctModel* model;
         CoefTable* coef_tab;
         SampleGenerationPanel* sample_panel;
      };
   }
}

#endif