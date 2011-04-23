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

			DctController(T* observing, DctModel* model, DctView<output_type>* view);

			virtual void notify();
		private:
			DctModel* model;
			DctView<output_type>* view;
			T* observing;
		};

		template <class T>
		DctController<T>::DctController(T* observing, DctModel* model, DctView<output_type>* view)
			: model(model), view(view), observing(observing)
		{}

		template <class T>
		void DctController<T>::notify()
		{
			std::vector<signal_type> sig(observing->getSignal());
			if(sig != model->signal())
			{
				model->setSignal(sig);
				view->setCoefficients(model->coefficients());
				observing->setCoefficientstRow(model->coefficients());
			}
			else
			{
				std::vector<output_type> out = observing->getCoefficients();
				if(out != model->coefficients())
				{
					model->setOutput(out);
					view->setCoefficients(model->coefficients());
					observing->setSampleRow(model->signal());
				}
			}
		}
	}
}

#endif