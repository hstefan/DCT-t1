#ifndef HSTEFAN_DCT_CONTROLLER_HPP
#define HSTEFAN_DCT_CONTROLLER_HPP

#include "DctView.hpp"
#include "DctModel.hpp"
#include "../util/Listener.hpp"
#include "CoefTable.hpp"
namespace hstefan
{
	namespace gui
	{
		template <class T = CoefTable>
		class DctController : public util::Listener
		{
		public:
			typedef DctModel::output_type output_type;
			typedef DctModel::signal_type signal_type;

			DctController(T* observing, DctModel* model, DctView* view);

			virtual void notify();
		private:
			DctModel* model;
			DctView* view;
			T* observing;
		};
		template <class T>
		DctController<T>::DctController(T* observing, DctModel* model, DctView* view)
			: model(model), view(view),observing(observing)
		{}

		template <class T>
		void DctController<T>::notify()
		{
			const std::vector<signal_type>& sig = T->getCoefficients();
			model->setSignal(sig);
			view->setCoefficients(model->coefficients());
		}
	}
}

#endif