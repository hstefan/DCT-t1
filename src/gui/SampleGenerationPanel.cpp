#include "SampleGenerationPanel.hpp"
#include <algorithm>

using namespace hstefan::gui;

SampleGenerationPanel::SampleGenerationPanel(scv::Point pi, unsigned int width, CoefTable* table)
	: scv::Panel(pi, width, PANEL_HEIGHT),
	table_ptr(table), sample_button(), len_label(scv::Point(W_SPACING, H_SPACING), "Tamanho"), 
	type_label(scv::Point(W_SPACING, H_SPACING*2 + len_label.getHeight()), "Tipo"),
	sample_box(scv::Point(width - std::max(type_label.getWidth(), len_label.getWidth()), H_SPACING + len_label.getHeight()), COMBO_WIDTH),
	len_box(scv::Point(width -  std::max(type_label.getWidth(), len_label.getWidth()), H_SPACING*2 + len_label.getHeight()), COMBO_WIDTH)
{
	addComponent(&sample_box);
	addComponent(&sample_button);
	addComponent(&type_label);
	addComponent(&sample_button);
	addComponent(&len_box);
}
