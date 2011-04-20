#include "DctModel.hpp"

using namespace hstefan;
using namespace gui;

DctModel::DctModel(const std::vector<signal_type>& signal)
	: m_signal(signal), m_output()
{
	applyDct();
}

const std::vector<DctModel::signal_type>& DctModel::signal() const
{
	return m_signal;
}
const std::vector<DctModel::output_type>& DctModel::coefficients() const
{
	return m_output;
}

void DctModel::setSignal(const std::vector<signal_type>& signal)
{
	m_signal = signal;
	applyDct();
}

void DctModel::applyDct()
{
	m_output.resize(m_signal.size());
	m_output = dct::DiscreteCosineTransform::fdct(m_signal);
}

void DctModel::setOutput(const std::vector<output_type>& output)
{
	m_output = output;
	applyIdct();
}

void DctModel::applyIdct()
{
	m_signal.resize(m_output.size());
	m_signal = dct::DiscreteCosineTransform::idct(m_output);
}
