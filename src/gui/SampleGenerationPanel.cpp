#include "SampleGenerationPanel.hpp"
#include <algorithm>

using namespace hstefan::gui;

SampleGenerationPanel::SampleGenerationPanel(scv::Point pi, unsigned int width, CoefTable* table)
	: scv::Panel(pi, width, PANEL_HEIGHT),
	table_ptr(table), len_label(scv::Point(W_SPACING, H_SPACING + 4), "Tamanho"),
	type_label(scv::Point(W_SPACING, H_SPACING*3 + len_label.getHeight()), "Tipo"),
	sample_box(scv::Point(len_label.getWidth() + W_SPACING, 3*H_SPACING + len_label.getHeight()), COMBO_WIDTH),
	len_box(scv::Point(len_label.getWidth() + W_SPACING, H_SPACING + 2) /*+ H_SPACING + len_label.getHeight()*2*/, COMBO_WIDTH),
	sample_button(this, PANEL_HEIGHT - 6*H_SPACING, getWidth() - 2*W_SPACING)
{
	sample_box.addItem("Aleatoria");
	sample_box.addItem("Linear");
	sample_box.setIndex(0);
	
	len_box.addItem("8");
	len_box.addItem("16");
	len_box.setIndex(1);

	addComponent(&sample_box);
	addComponent(&sample_button);
	addComponent(&type_label);
	addComponent(&len_label);
	addComponent(&len_box);
}
