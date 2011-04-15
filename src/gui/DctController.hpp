#ifndef HSTEFAN_DCT_CONTROLLER_HPP
#define HSTEFAN_DCT_CONTROLLER_HPP

#include "DctView.hpp"
#include "DctModel.hpp"

namespace hstefan
{
	namespace gui
	{
		class DctController
		{
		public:
			DctController(DctModel* model, DctView* view);
		private:
			DctModel* model;
			DctView* view;
		};
	}
}

#endif